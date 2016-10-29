/**
 * @file cmdline.c
 * @author Sebastien CAUX (sebcaux) \
 * @copyright Robotips 2016
 *
 * @date October 10, 2016, 10:44 PM
 *
 * @brief Base implementation for cmdline module
 */

#include "cmdline.h"
#include "cmdline_curses.h"

#ifdef TEST_CMDLINE
  #include <termios.h>
  #include <stdio.h>
  #include <assert.h>
  #include <unistd.h>
  #include <stdlib.h>
  #define device_read(a,b,c) read(0, (b), (c))
  #define device_write(a,b,c) write(1, (b), (c))
#endif

#include <string.h>
#include <ctype.h>
#include "cmd/cmd.h"

rt_dev_t cmdline_device_in;
rt_dev_t cmdline_device_out;

void cmdline_setDevice(rt_dev_t deviceIn, rt_dev_t deviceOut)
{
    cmdline_device_in = deviceIn;
    cmdline_device_out = deviceOut;
}

#define BUFF_SIZ 100
#define LINE_SIZ 100

char cmdline_buffread[BUFF_SIZ];
char cmdline_line[LINE_SIZ];
char cmdline_oldline[LINE_SIZ];
unsigned int cmdline_id, cmdline_end;
char cmdline_escape = 0;

void cmdline_endofline()
{
    char cmd[10];
    if(cmdline_id == cmdline_end)
        return;
    cmdline_curses_right(cmd, cmdline_end - cmdline_id);
    device_write(cmdline_device_out, cmd, strlen(cmd)); // move cursor cmdline_id to the left
    cmdline_id = cmdline_end;
}

void cmdline_startofline()
{
    char cmd[10];
    if(cmdline_id==0)
        return;
    cmdline_curses_left(cmd, cmdline_id);
    device_write(cmdline_device_out, cmd, strlen(cmd)); // move cursor cmdline_id to the left
    cmdline_id = 0;
}

void cmdline_right()
{
    char cmd[10];
    if(cmdline_id==cmdline_end)
        return;
    cmdline_id++;

    cmdline_curses_right(cmd, 1);
    device_write(cmdline_device_out, cmd, strlen(cmd)); // move cursor 1 line right
}

void cmdline_left()
{
    char cmd[10];
    if(cmdline_id==0)
        return;
    cmdline_id--;

    cmdline_curses_left(cmd, 1);
    device_write(cmdline_device_out, cmd, strlen(cmd)); // move cursor 1 line right
}

void cmdline_up()
{
    // clear line
    cmdline_startofline();
    memset(cmdline_line, ' ', cmdline_end);
    device_write(cmdline_device_out, cmdline_line, cmdline_end);
    cmdline_id = cmdline_end;

    // get old line
    cmdline_startofline();
    strcpy(cmdline_line, cmdline_oldline);
    cmdline_end = strlen(cmdline_line);
    cmdline_id = cmdline_end;
    if(cmdline_end>0)
        device_write(cmdline_device_out, cmdline_line, cmdline_end);
}

void cmdline_down()
{
}

void cmdline_clear()
{
    char cmd[10];
    cmdline_curses_clear(cmd);
    device_write(cmdline_device_out, cmd, strlen(cmd));
}

void cmdline_reset()
{
    char cmd[10];
    cmdline_id = 0;
    cmdline_escape = 0;
    cmdline_end = 0;
    cmdline_curses_left(cmd, 200);
    device_write(cmdline_device_out, cmd, strlen(cmd)); // move cursor 200 column before
    device_write(cmdline_device_out, "> ", 2);
}

void cmdline_init()
{
    cmdline_oldline[0] = 0;
    cmdline_clear();
    cmdline_reset();
}

void cmdline_processline(char *line)
{
    int ret;
    if(line[0]!=0)
    {
        ret = cmd_exec(line);
        if(ret != 0)
        {
            device_write(cmdline_device_out, "Invalid command '", 17);
            device_write(cmdline_device_out, cmdline_line, strlen(cmdline_line));
            device_write(cmdline_device_out, "'\r\n", 3);
        }
    }

    cmdline_reset();
}

void cmdline_pushchar(char c)
{
    char bf[1];
    if(cmdline_id >= LINE_SIZ - 1) // line full
        return;
    if(cmdline_id == cmdline_end) // end of line
    {
        cmdline_end++;
        cmdline_line[cmdline_id] = c;
        cmdline_id++;
        bf[0] = c;
        device_write(cmdline_device_out, bf, 1);
    }
    else    // middle of line (insert)
    {
        char cmd[10];
        int i;
        bf[0] = c;
        device_write(cmdline_device_out, bf, 1);
        device_write(cmdline_device_out, cmdline_line + cmdline_id, cmdline_end - cmdline_id);
        cmdline_curses_left(cmd, cmdline_end - cmdline_id);
        device_write(cmdline_device_out, cmd, strlen(cmd));
        cmdline_end++;
        for(i = cmdline_end - 1; i > cmdline_id; i--)
            cmdline_line[i] = cmdline_line[i-1];
        cmdline_line[cmdline_id] = c;
        cmdline_id++;
    }
}

void cmdline_backspace()
{
    int i;
    char cmd[10];
    if(cmdline_id==0)
        return;

    cmdline_curses_left(cmd, 1);
    device_write(cmdline_device_out, cmd, strlen(cmd)); // move cursor 1 line right
    cmdline_line[cmdline_end]=' ';
    device_write(cmdline_device_out, cmdline_line + cmdline_id, cmdline_end - cmdline_id + 1);
    cmdline_id--;
    for(i = cmdline_id+1; i < cmdline_end; i++)
        cmdline_line[i-1] = cmdline_line[i];

    cmdline_curses_left(cmd, cmdline_end - cmdline_id);
    device_write(cmdline_device_out, cmd, strlen(cmd)); // move cursor 1 line right
    cmdline_end--;
}

uint8_t cmdline_getLine()
{
    char c;
    ssize_t byte_read = device_read(cmdline_device_in, cmdline_buffread, BUFF_SIZ);
    if(byte_read > 0)
    {
        uint16_t i;
        uint8_t valid = 0;
        for (i = 0; i < byte_read; i++)
        {
            c = *(cmdline_buffread + i);
            //printf("ALL%d\n",(int)c);

            // Ctrl + C or Ctrl + D
            if(c==3 || c==4)
#ifdef TEST_CMDLINE
                exit(0);
#else
                {
                    device_write(cmdline_device_out, "^C\n\r", 4);
                    cmdline_reset();
                    continue;
                }
#endif
            // Ctrl + A (start of line)
            if(c==1)
            {
                cmdline_startofline();
                continue;
            }
            // Ctrl + E (end of line)
            if(c==5)
            {
                cmdline_endofline();
                continue;
            }

            // backspace (clear previous char)
            if(c==127)
            {
                cmdline_backspace();
                continue;
            }

            // esc char
            if(c==27)
            {
                cmdline_escape = 1;
                continue;
            }
            if(cmdline_escape>0)
            {
                if(cmdline_escape==1)
                {
                    if(c==91) // arrows
                        cmdline_escape=2;
                    else if(c==79) // start/end
                        cmdline_escape=64;
                    else
                        cmdline_escape=0;
                    continue;
                }
                if(cmdline_escape==2)
                {
                    if(c==65)
                        cmdline_up();
                    if(c==66)
                        cmdline_down();
                    if(c==67)
                        cmdline_right();
                    if(c==68)
                        cmdline_left();
                    cmdline_escape=0;
                    continue;
                }
                if(cmdline_escape==64)
                {
                    if(c==72)
                        cmdline_startofline();
                    if(c==70)
                        cmdline_endofline();
                    cmdline_escape=0;
                    continue;
                }
            }

            // end of line
            if (cmdline_buffread[i] == '\r')
            {
                char cmd[10];
                cmdline_curses_left(cmd, 200);
                device_write(cmdline_device_out, cmd, strlen(cmd)); // move cursor 200 column before
                device_write(cmdline_device_out, "\n\r", 2);
                valid = 1;
                break;
            }

            // echo char and put into line
            if(isprint(c))
                cmdline_pushchar(c);
        }

        if (valid == 0)
            return 0;

        // process line
        cmdline_line[cmdline_end] = 0;
        if(cmdline_end!=0)
            strcpy(cmdline_oldline, cmdline_line);

        return 1;
    }
    return 0;
}

void cmdline_task()
{
	if(cmdline_getLine()!=0)
    {
        cmdline_processline(cmdline_line);
    }
    //usleep(500000);
}

#ifdef TEST_CMDLINE
struct termios t_save;

void bye (void)
{
    tcsetattr(0, TCSANOW, &t_save);
    puts ("Goodbye, cruel world....");
}

int main(void)
{
    int i;
    char buff[BUFF_SIZ];

    struct termios t;
    atexit (bye);

    tcgetattr(0, &t);
    tcgetattr(0, &t_save);

    t.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                           | INLCR | IGNCR | ICRNL | IXON);
    t.c_oflag &= ~OPOST;
    t.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tcsetattr(0, TCSANOW, &t);

    cmdline_init();

    while(1)
        cmdline_task();
}
#endif
