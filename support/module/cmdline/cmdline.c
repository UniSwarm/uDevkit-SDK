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

#ifdef TEST_CMDLINE
  #include <curses.h>
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

rt_dev_t cmdline_device_in;
rt_dev_t cmdline_device_out;

void cmdline_setDevice(rt_dev_t deviceIn, rt_dev_t deviceOut)
{
    cmdline_device_in = deviceIn;
    cmdline_device_out = deviceOut;
}

char buffread[100];

char cmdline_line[200];
unsigned int cmdline_id, cmdline_end;
char cmdline_escape = 0;

void cmdline_up()
{
    device_write(cmdline_device_out,"\033[1A", 4); // move cursor 1 line up
}

void cmdline_down()
{
    device_write(cmdline_device_out,"\033[1B", 4); // move cursor 1 line down
}

void cmdline_right()
{
    if(cmdline_id==cmdline_end)
        return;
    cmdline_id++;
    device_write(cmdline_device_out,"\033[1C", 4); // move cursor 1 line right
}

void cmdline_left()
{
    if(cmdline_id==0)
        return;
    cmdline_id--;
    device_write(cmdline_device_out,"\033[1D", 4); // move cursor 1 line left
}

void cmdline_clear()
{
    device_write(cmdline_device_out,"\033[2J", 4); // clear screen
}

void cmdline_reset()
{
    cmdline_id = 0;
    cmdline_escape = 0;
    cmdline_end = 0;
}

void cmdline_init()
{
    cmdline_clear();
    cmdline_reset();
}

void cmdline_processline(char *line)
{
    // out line
    device_write(cmdline_device_out, line, strlen(line));
    device_write(cmdline_device_out, "\r\n", 2);
    device_write(cmdline_device_out,"\033[200D", 6); // move cursor 200 column before
}

void cmdline_pushchar(char c)
{
    char bf[1];
    if(cmdline_id == cmdline_end)
        cmdline_end++;
    cmdline_line[cmdline_id] = c;
    cmdline_id++;
    bf[0] = c;
    device_write(cmdline_device_out, bf, 1);
}

uint8_t cmdline_getLine()
{
    char c;
    ssize_t byte_read = device_read(cmdline_device_in, buffread, 100);
    if(byte_read > 0)
    {
        uint16_t i;
        uint8_t valid = 0;
        for (i = 0; i < byte_read; i++)
        {
            c = *(buffread + i);

            // Ctrl + C or Ctrl + D
            if(c==3 || c==4)
#ifdef TEST_CMDLINE
                exit(0);
#else
                {
                    cmdline_reset();
                    continue;
                }
#endif

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
                    if(c!=91)
                        cmdline_escape=0;
                    else
                        cmdline_escape=2;
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
            }
            
            // end of line
            if (buffread[i] == '\r')
            {
                device_write(cmdline_device_out,"\033[200D", 6); // move cursor 100 column before

                device_write(cmdline_device_out, "\n\r", 1);
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
        cmdline_processline(cmdline_line);
        cmdline_reset();

        return 1;
    }
    return 0;
}

void cmdline_task()
{
	if(cmdline_getLine()!=0)
    {
        //exit(0);
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
    char buff[100];

    struct termios t;
    atexit (bye);

    tcgetattr(0, &t);
    tcgetattr(0, &t_save);

    t.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                           | INLCR | IGNCR | ICRNL | IXON);
    t.c_oflag &= ~OPOST;
    t.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tcsetattr(0, TCSANOW, &t);

    while(1)
        cmdline_task();
}
#endif
