/**
 * @file cmdline_curses.h
 * @author Sebastien CAUX (sebcaux) \
 * @copyright Robotips 2016
 *
 * @date October 28, 2016, 10:44 PM
 *
 * @brief Special curses commands to move cursor, clear screen...
 */

#ifndef CMDLINE_CURSES_H
#define CMDLINE_CURSES_H

#include <stdint.h>
#include <stdio.h>

#define cmdline_curses_buildcmdnum(cmd, c, num) sprintf(cmd, "\033[%d%c", num, c)
#define cmdline_curses_up(cmd, num) cmdline_curses_buildcmdnum((cmd), 'A', (num))
#define cmdline_curses_down(cmd, num) cmdline_curses_buildcmdnum((cmd), 'B', (num))
#define cmdline_curses_right(cmd, num) cmdline_curses_buildcmdnum((cmd), 'C', (num))
#define cmdline_curses_left(cmd, num) cmdline_curses_buildcmdnum((cmd), 'D', (num))
#define cmdline_curses_clear(cmd) cmdline_curses_buildcmdnum((cmd), 'J', 2)

#endif // CMDLINE_CURSES_H
