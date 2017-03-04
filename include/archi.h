/**
 * @file archi.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 12, 2016, 08:33 AM
 *
 * @brief Architecture low level definitions for all supported architectures
 */

#ifndef ARCHI_H
#define ARCHI_H

// ======== Microchip 16 bits family =======
#if defined(ARCHI_dspic30f)
 #include "../support/archi/dspic30f/dspic30f.h"
#elif defined(ARCHI_dspic33ep)
 #include "../support/archi/dspic33ep/dspic33ep.h"
#elif defined(ARCHI_dspic33ev)
 #include "../support/archi/dspic33ev/dspic33ev.h"
#elif defined(ARCHI_dspic33fj)
 #include "../support/archi/dspic33fj/dspic33fj.h"
#elif defined(ARCHI_pic24ep)
 #include "../support/archi/pic24ep/pic24ep.h"
#elif defined(ARCHI_pic24f)
 #include "../support/archi/pic24f/pic24f.h"
#elif defined(ARCHI_pic24fj)
 #include "../support/archi/pic24fj/pic24fj.h"
#elif defined(ARCHI_pic24fv)
 #include "../support/archi/pic24fv/pic24fv.h"
#elif defined(ARCHI_pic24hj)
 #include "../support/archi/pic24hj/pic24hj.h"

// ======== Microchip 32 bits family =======
#elif defined(ARCHI_pic32mx)
 #include "../support/archi/pic32mx/pic32mx.h"
#elif defined(ARCHI_pic32mzda)
 #include "../support/archi/pic32mzda/pic32mzda.h"
#elif defined(ARCHI_pic32mzec)
 #include "../support/archi/pic32mzec/pic32mzec.h"
#elif defined(ARCHI_pic32mzef)
 #include "../support/archi/pic32mzef/pic32mzef.h"
#elif defined(ARCHI_pic32mm)
 #include "../support/archi/pic32mm/pic32mm.h"
#elif defined(ARCHI_pic32mk)
 #include "../support/archi/pic32mk/pic32mk.h"
#else
 #error Unsuported ARCHI
#endif

#if defined(SIMULATOR)
 #include "../support/archi/simulator/simulator.h"

 #define board_init() board_init(); simulator_init()
 #define robot_init() robot_init(); simulator_init()
#endif

#endif // ARCHI_H
