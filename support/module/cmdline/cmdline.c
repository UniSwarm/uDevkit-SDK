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

#include "cmd/cmd.h"
#include <ctype.h>
#include <string.h>

rt_dev_t _cmdline_device_in;
rt_dev_t _cmdline_device_out;

#define BUFFREAD_SIZ 50
#define LINE_SIZ     100
#define HISTORY_MAX  5

// line parsing
char cmdline_escape = 0;
char cmdline_buffread[BUFFREAD_SIZ];

// current line
int cmdline_id = 0, cmdline_end = 0;
char cmdline_line[LINE_SIZ];

// history and current line
int cmdline_history_end = 0, cmdline_history_id = -1;
char cmdline_oldline[HISTORY_MAX][LINE_SIZ];

static void _cmdline_endofline(void);
static void _cmdline_startofline(void);
static void _cmdline_right(void);
static void _cmdline_left(void);
static void _cmdline_replaceLineContent(const char *newline);
static void _cmdline_up(void);
static void _cmdline_down(void);
static void _cmdline_clear(void);
static void _cmdline_processline(const char *line);
static void _cmdline_reset(void);
static void _cmdline_pushchar(const char c);
static void _cmdline_backspace(void);
static uint8_t _cmdline_getLine(void);

void _cmdline_endofline(void)
{
    char cmd[10];
    if (cmdline_id == cmdline_end)
    {
        return;
    }
    cmdline_curses_right(cmd, cmdline_end - cmdline_id);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor cmdline_id to the left
    cmdline_id = cmdline_end;
}

void _cmdline_startofline(void)
{
    char cmd[10];
    if (cmdline_id == 0)
    {
        return;
    }
    cmdline_curses_left(cmd, cmdline_id);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor cmdline_id to the left
    cmdline_id = 0;
}

void _cmdline_right(void)
{
    char cmd[10];
    if (cmdline_id == cmdline_end)
    {
        return;
    }
    cmdline_id++;

    cmdline_curses_right(cmd, 1);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 1 line right
}

void _cmdline_left(void)
{
    char cmd[10];
    if (cmdline_id == 0)
    {
        return;
    }
    cmdline_id--;

    cmdline_curses_left(cmd, 1);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 1 line right
}

void _cmdline_replaceLineContent(const char *newline)
{
    // clear line
    _cmdline_startofline();
    memset(cmdline_line, ' ', cmdline_end);
    device_write(_cmdline_device_out, cmdline_line, cmdline_end);
    cmdline_id = cmdline_end;

    // get old line
    _cmdline_startofline();
    strcpy(cmdline_line, newline);
    cmdline_end = strlen(cmdline_line);
    cmdline_id = cmdline_end;
    if (cmdline_end > 0)
    {
        device_write(_cmdline_device_out, cmdline_line, cmdline_end);
    }
}

void _cmdline_up(void)
{
    if (cmdline_history_id >= cmdline_history_end)
    {
        return;
    }
    cmdline_history_id++;
    _cmdline_replaceLineContent(cmdline_oldline[cmdline_history_id]);
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
    _cmdline_replaceLineContent(cmdline_oldline[cmdline_history_id]);
}

void _cmdline_clear(void)
{
    char cmd[10];
    cmdline_curses_clear(cmd);
    device_write(_cmdline_device_out, cmd, strlen(cmd));
}

void _cmdline_reset(void)
{
    char cmd[10];
    cmdline_id = 0;
    cmdline_escape = 0;
    cmdline_end = 0;
    cmdline_history_id = -1;
    cmdline_curses_left(cmd, 200);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 200 column before
    device_write(_cmdline_device_out, "> ", 2);
}

void _cmdline_processline(const char *line)
{
    int i;
    int ret;
    if (line[0] != 0)
    {
        // save history
        for (i = cmdline_history_end; i > 0; i--)
        {
            strcpy(cmdline_oldline[i], cmdline_oldline[i - 1]);
        }
        if (cmdline_history_end < HISTORY_MAX - 1)
        {
            cmdline_history_end++;
        }
        strcpy(cmdline_oldline[0], cmdline_line);
        cmdline_history_id = -1;

        ret = cmd_exec(line);
        if (ret < 0)
        {
            device_write(_cmdline_device_out, "Invalid command '", 17);
            device_write(_cmdline_device_out, cmdline_line, strlen(cmdline_line));
            device_write(_cmdline_device_out, "'\r\n", 3);
        }
        else if (ret > 0)
        {
            device_write(_cmdline_device_out, "'", 1);
            device_write(_cmdline_device_out, cmdline_line, strlen(cmdline_line));
            device_write(_cmdline_device_out, "' failed to exec\r\n", 18);
        }
    }

    _cmdline_reset();
}

void _cmdline_pushchar(const char c)
{
    char bf[1];
    if (cmdline_id >= LINE_SIZ - 1)  // line full
    {
        return;
    }
    if (cmdline_id == cmdline_end)  // end of line
    {
        cmdline_end++;
        cmdline_line[cmdline_id] = c;
        cmdline_id++;
        bf[0] = c;
        device_write(_cmdline_device_out, bf, 1);
    }
    else  // middle of line (insert)
    {
        char cmd[10];
        bf[0] = c;
        device_write(_cmdline_device_out, bf, 1);
        device_write(_cmdline_device_out, cmdline_line + cmdline_id, cmdline_end - cmdline_id);
        cmdline_curses_left(cmd, cmdline_end - cmdline_id);
        device_write(_cmdline_device_out, cmd, strlen(cmd));
        cmdline_end++;
        for (int i = cmdline_end - 1; i > cmdline_id; i--)
        {
            cmdline_line[i] = cmdline_line[i - 1];
        }
        cmdline_line[cmdline_id] = c;
        cmdline_id++;
    }
}

void _cmdline_backspace(void)
{
    int i;
    char cmd[10];
    if (cmdline_id == 0)
    {
        return;
    }

    cmdline_curses_left(cmd, 1);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 1 line right
    cmdline_line[cmdline_end] = ' ';
    device_write(_cmdline_device_out, cmdline_line + cmdline_id, cmdline_end - cmdline_id + 1);
    cmdline_id--;
    for (i = cmdline_id + 1; i < cmdline_end; i++)
    {
        cmdline_line[i - 1] = cmdline_line[i];
    }

    cmdline_curses_left(cmd, cmdline_end - cmdline_id);
    device_write(_cmdline_device_out, cmd, strlen(cmd));  // move cursor 1 line right
    cmdline_end--;
}

uint8_t _cmdline_getLine(void)
{
    char c;
    ssize_t byte_read = device_read(_cmdline_device_in, cmdline_buffread, BUFFREAD_SIZ);
    if (byte_read > 0)
    {
        uint16_t i;
        uint8_t valid = 0;
        for (i = 0; i < byte_read; i++)
        {
            c = *(cmdline_buffread + i);
            // printf("ALL%d\n",(int)c);

            // Ctrl + C or Ctrl + D
            if (c == 3 || c == 4)
#ifdef TEST_CMDLINE
                exit(0);
#else
            {
                device_write(_cmdline_device_out, "^C\n\r", 4);
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
                cmdline_escape = 1;
                continue;
            }
            if (cmdline_escape > 0)
            {
                if (cmdline_escape == 1)
                {
                    if (c == 91)  // arrows
                    {
                        cmdline_escape = 2;
                    }
                    else if (c == 79)  // start/end
                    {
                        cmdline_escape = 64;
                    }
                    else
                    {
                        cmdline_escape = 0;
                    }
                    continue;
                }
                if (cmdline_escape == 2)
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
                    cmdline_escape = 0;
                    continue;
                }
                if (cmdline_escape == 64)
                {
                    if (c == 72)
                    {
                        _cmdline_startofline();
                    }
                    if (c == 70)
                    {
                        _cmdline_endofline();
                    }
                    cmdline_escape = 0;
                    continue;
                }
            }

            // end of line
            if (cmdline_buffread[i] == '\r')
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
        cmdline_line[cmdline_end] = 0;

        return 1;
    }
    return 0;
}

void cmdline_init(void)
{
    _cmdline_clear();
    _cmdline_reset();
}

void cmdline_setDevice(rt_dev_t deviceIn, rt_dev_t deviceOut)
{
    _cmdline_device_in = deviceIn;
    _cmdline_device_out = deviceOut;
}

void cmdline_task(void)
{
    if (_cmdline_getLine() != 0)
    {
        _cmdline_processline(cmdline_line);
    }
    // usleep(500000);
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
    }
}
#endif
