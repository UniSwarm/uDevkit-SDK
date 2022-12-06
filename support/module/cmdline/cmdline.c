/**
 * @file cmdline.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date October 10, 2016, 10:44 PM
 *
 * @brief Base implementation for cmdline module
 */

#include "cmdline.h"

#include "cmd/cmd.h"
#include "cmdline_curses.h"

#ifdef TEST_CMDLINE
#    include <assert.h>
#    include <stdio.h>
#    include <stdlib.h>
#    include <termios.h>
#    include <unistd.h>
#    define device_read(a, b, c)  read(0, (b), (c))
#    define device_write(a, b, c) write(1, (b), (c))
#endif

#include <ctype.h>
#include <limits.h>
#include <string.h>

rt_dev_t _cmdline_device_in;
rt_dev_t _cmdline_device_out;
enum
{
    CMDLINE_STATE_INIT,
    CMDLINE_STATE_RUN,
} _cmdline_state = CMDLINE_STATE_INIT;

#define CMDLINE_BUFFREAD_SIZE 50
#define CMDLINE_LINE_SIZE     100
#define CMDLINE_HISTORY_COUNT 5

// line parsing
char _cmdline_escape = 0;
char _cmdline_buffread[CMDLINE_BUFFREAD_SIZE];

// current line
int _cmdline_id = 0;
int _cmdline_end = 0;
char _cmdline_line[CMDLINE_LINE_SIZE];

// history and current line
int _cmdline_history_end = 0, cmdline_history_id = -1;
char _cmdline_oldline[CMDLINE_HISTORY_COUNT][CMDLINE_LINE_SIZE];

static void _cmdline_endofline(void);
static void _cmdline_startofline(void);
static void _cmdline_right(void);
static void _cmdline_left(void);
static void _cmdline_replaceLineContent(const char *newline);
static void _cmdline_up(void);
static void _cmdline_down(void);
static void _cmdline_clear(void);
static void _cmdline_processline(char *line);
static void _cmdline_newline(void);
static void _cmdline_reset(void);
static void _cmdline_pushchar(const char c);
static void _cmdline_backspace(void);
static uint8_t _cmdline_getLine(void);

void _cmdline_endofline(void)
{
    char cmd[10];
    if (_cmdline_id == _cmdline_end)
    {
        return;
    }
    cmdline_curses_right(cmd, _cmdline_end - _cmdline_id);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor _cmdline_id to the left
    _cmdline_id = _cmdline_end;
}

void _cmdline_startofline(void)
{
    char cmd[10];
    if (_cmdline_id == 0)
    {
        return;
    }
    cmdline_curses_left(cmd, _cmdline_id);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor _cmdline_id to the left
    _cmdline_id = 0;
}

void _cmdline_right(void)
{
    char cmd[10];
    if (_cmdline_id == _cmdline_end)
    {
        return;
    }
    _cmdline_id++;

    cmdline_curses_right(cmd, 1);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 1 line right
}

void _cmdline_left(void)
{
    char cmd[10];
    if (_cmdline_id == 0)
    {
        return;
    }
    _cmdline_id--;

    cmdline_curses_left(cmd, 1);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 1 line right
}

void _cmdline_replaceLineContent(const char *newline)
{
    // clear line
    _cmdline_startofline();
    memset(_cmdline_line, ' ', _cmdline_end);
    device_write(_cmdline_device_out, _cmdline_line, _cmdline_end);
    _cmdline_id = _cmdline_end;

    // get old line
    _cmdline_startofline();
    strcpy(_cmdline_line, newline);
    _cmdline_end = strlen(_cmdline_line);
    _cmdline_id = _cmdline_end;
    if (_cmdline_end > 0)
    {
        device_write(_cmdline_device_out, _cmdline_line, _cmdline_end);
    }
}

void _cmdline_up(void)
{
    if (cmdline_history_id >= _cmdline_history_end)
    {
        return;
    }
    cmdline_history_id++;
    _cmdline_replaceLineContent(_cmdline_oldline[cmdline_history_id]);
}

void _cmdline_down(void)
{
    if (cmdline_history_id == 0)
    {
        cmdline_history_id = -1;
        _cmdline_replaceLineContent("");
        return;
    }
    if (cmdline_history_id == -1)
    {
        return;
    }
    cmdline_history_id--;
    _cmdline_replaceLineContent(_cmdline_oldline[cmdline_history_id]);
}

void _cmdline_clear(void)
{
    char cmd[10];
    cmdline_curses_clear(cmd);
    device_write(_cmdline_device_out, cmd, strlen(cmd));
}

void _cmdline_newline(void)
{
    char cmd[10];
    _cmdline_id = 0;
    _cmdline_escape = 0;
    _cmdline_end = 0;
    cmdline_history_id = -1;
    cmdline_curses_left(cmd, 200);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 200 column before
}

void _cmdline_reset(void)
{
    _cmdline_newline();
    device_write(_cmdline_device_out, "> ", 2);
}

void _cmdline_processline(char *line)
{
    if (line[0] == 0)
    {
        _cmdline_reset();
        return;
    }

    // save history
    for (int i = _cmdline_history_end; i > 0; i--)
    {
        strcpy(_cmdline_oldline[i], _cmdline_oldline[i - 1]);
    }
    if (_cmdline_history_end < CMDLINE_HISTORY_COUNT - 1)
    {
        _cmdline_history_end++;
    }
    strcpy(_cmdline_oldline[0], _cmdline_line);
    cmdline_history_id = -1;

    int ret = cmd_exec(line);

    if (ret > 0)  // command not finished
    {
        _cmdline_newline();
        return;
    }

    if (ret == INT_MIN)  // command not found
    {
        device_write(_cmdline_device_out, "Invalid command '", 17);
        device_write(_cmdline_device_out, _cmdline_line, strlen(_cmdline_line));
        device_write(_cmdline_device_out, "'\r\n", 3);
        _cmdline_reset();
        return;
    }

    if (ret < 0)  // error in command
    {
        device_write(_cmdline_device_out, "'", 1);
        device_write(_cmdline_device_out, _cmdline_line, strlen(_cmdline_line));
        device_write(_cmdline_device_out, "' failed to exec\r\n", 18);
        _cmdline_reset();
        return;
    }

    if (ret == 0)  // command finished and whell executed
    {
        _cmdline_reset();
        return;
    }
}

void _cmdline_pushchar(const char c)
{
    char bf[1];
    if (_cmdline_id >= CMDLINE_LINE_SIZE - 1)  // line full
    {
        return;
    }

    if (_cmdline_id == _cmdline_end)  // end of line
    {
        _cmdline_end++;
        _cmdline_line[_cmdline_id] = c;
        _cmdline_id++;
        bf[0] = c;
        device_write(_cmdline_device_out, bf, 1);
    }
    else  // middle of line (insert)
    {
        char cmd[10];
        bf[0] = c;
        device_write(_cmdline_device_out, bf, 1);
        device_write(_cmdline_device_out, _cmdline_line + _cmdline_id, _cmdline_end - _cmdline_id);
        cmdline_curses_left(cmd, _cmdline_end - _cmdline_id);
        device_write(_cmdline_device_out, cmd, strlen(cmd));
        _cmdline_end++;
        for (int i = _cmdline_end - 1; i > _cmdline_id; i--)
        {
            _cmdline_line[i] = _cmdline_line[i - 1];
        }
        _cmdline_line[_cmdline_id] = c;
        _cmdline_id++;
    }
}

void _cmdline_backspace(void)
{
    char cmd[10];
    if (_cmdline_id == 0)
    {
        return;
    }

    cmdline_curses_left(cmd, 1);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 1 line right
    _cmdline_line[_cmdline_end] = ' ';
    device_write(_cmdline_device_out, _cmdline_line + _cmdline_id, _cmdline_end - _cmdline_id + 1);
    _cmdline_id--;
    for (int i = _cmdline_id + 1; i < _cmdline_end; i++)
    {
        _cmdline_line[i - 1] = _cmdline_line[i];
    }

    cmdline_curses_left(cmd, _cmdline_end - _cmdline_id);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 1 line right
    _cmdline_end--;
}

uint8_t _cmdline_getLine(void)
{
    ssize_t byte_read = device_read(_cmdline_device_in, _cmdline_buffread, CMDLINE_BUFFREAD_SIZE);
    if (byte_read > 0)
    {
        uint16_t i;
        uint8_t valid = 0;
        for (i = 0; i < byte_read; i++)
        {
            char c = *(_cmdline_buffread + i);

            // Ctrl + C or Ctrl + D
            if (c == 3 || c == 4)
#ifdef TEST_CMDLINE
                exit(0);
#else
            {
                device_write(_cmdline_device_out, "^C\n\r", 4);
                cmd_setTask(NULL);  // finished current task
                _cmdline_reset();
                continue;
            }
#endif
            // Ctrl + A (start of line)
            if (c == 1)
            {
                _cmdline_startofline();
                continue;
            }
            // Ctrl + E (end of line)
            if (c == 5)
            {
                _cmdline_endofline();
                continue;
            }

            // backspace (clear previous char)
            if (c == 127)
            {
                _cmdline_backspace();
                continue;
            }

            // esc char
            if (c == 27)
            {
                _cmdline_escape = 1;
                continue;
            }
            if (_cmdline_escape > 0)
            {
                if (_cmdline_escape == 1)
                {
                    if (c == 91)  // arrows
                    {
                        _cmdline_escape = 2;
                    }
                    else if (c == 79)  // start/end
                    {
                        _cmdline_escape = 64;
                    }
                    else
                    {
                        _cmdline_escape = 0;
                    }
                    continue;
                }
                if (_cmdline_escape == 2)
                {
                    if (c == 65)
                    {
                        _cmdline_up();
                    }
                    if (c == 66)
                    {
                        _cmdline_down();
                    }
                    if (c == 67)
                    {
                        _cmdline_right();
                    }
                    if (c == 68)
                    {
                        _cmdline_left();
                    }
                    _cmdline_escape = 0;
                    continue;
                }
                if (_cmdline_escape == 64)
                {
                    if (c == 72)
                    {
                        _cmdline_startofline();
                    }
                    if (c == 70)
                    {
                        _cmdline_endofline();
                    }
                    _cmdline_escape = 0;
                    continue;
                }
            }

            // end of line
            if (_cmdline_buffread[i] == '\r')
            {
                char cmd[10];
                cmdline_curses_left(cmd, 200);
                device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 200 column before
                device_write(_cmdline_device_out, "\n\r", 2);
                valid = 1;
                break;
            }

            // echo char and put into line
            if (isprint(c))
            {
                _cmdline_pushchar(c);
            }
        }

        if (valid == 0)
        {
            return 0;
        }

        // mark end of line line
        _cmdline_line[_cmdline_end] = 0;

        return 1;
    }
    return 0;
}

void cmdline_init(void)
{
    _cmdline_state = CMDLINE_STATE_RUN;
}

void cmdline_setDevice(rt_dev_t deviceIn, rt_dev_t deviceOut)
{
    _cmdline_device_in = deviceIn;
    _cmdline_device_out = deviceOut;
}

void cmdline_task(void)
{
    switch (_cmdline_state)
    {
        case CMDLINE_STATE_INIT:
            _cmdline_clear();
            _cmdline_reset();
            _cmdline_state = CMDLINE_STATE_RUN;
            break;

        case CMDLINE_STATE_RUN:
            if (_cmdline_getLine() != 0)
            {
                _cmdline_processline(_cmdline_line);
            }
            cmd_task();
            break;
    }
}

#ifdef TEST_CMDLINE
struct termios t_save;

void bye(void)
{
    tcsetattr(0, TCSANOW, &t_save);
    puts("Goodbye, cruel world....");
}

int main(void)
{
    struct termios t;
    atexit(bye);

    tcgetattr(0, &t);
    tcgetattr(0, &t_save);

    t.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    t.c_oflag &= ~OPOST;
    t.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tcsetattr(0, TCSANOW, &t);

    cmdline_init();

    while (1)
    {
        cmdline_task();
        usleep(500000);
    }
}
#endif

int cmdline_addCommand(const char name[10], int (*cmdFnPtr)(int, char **))
{
    return cmd_addCommand(name, cmdFnPtr);
}
