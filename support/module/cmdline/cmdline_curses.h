/**
 * @file cmdline_curses.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 28, 2016, 10:44 PM
 *
 * @brief Special curses commands to move cursor, clear screen...
 */

#ifndef CMDLINE_CURSES_H
#define CMDLINE_CURSES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

#define cmdline_curses_buildcmdnum(cmd, c, num) sprintf(cmd, "\033[%d%c", num, c)
#define cmdline_curses_up(cmd, num)             cmdline_curses_buildcmdnum((cmd), 'A', (num))
#define cmdline_curses_down(cmd, num)           cmdline_curses_buildcmdnum((cmd), 'B', (num))
#define cmdline_curses_right(cmd, num)          cmdline_curses_buildcmdnum((cmd), 'C', (num))
#define cmdline_curses_left(cmd, num)           cmdline_curses_buildcmdnum((cmd), 'D', (num))
#define cmdline_curses_clear(cmd)               cmdline_curses_buildcmdnum((cmd), 'J', 2)

#define CMDLINE_NRM "\x1B[0m"
#define CMDLINE_RED "\x1B[31m"
#define CMDLINE_GRN "\x1B[32m"
#define CMDLINE_YEL "\x1B[33m"
#define CMDLINE_BLU "\x1B[34m"
#define CMDLINE_MAG "\x1B[35m"
#define CMDLINE_CYN "\x1B[36m"
#define CMDLINE_WHT "\x1B[37m"

#ifdef __cplusplus
}
#endif

#endif  // CMDLINE_CURSES_H
