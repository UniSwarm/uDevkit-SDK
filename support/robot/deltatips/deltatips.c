/**
 * @file deltatips.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date September 23, 2016, 04:06 PM
 *
 * @brief Code for deltaTips robot from Robotips
 */

#include "deltatips.h"

#include "module/mrobot.h"

int init_robot()
{
    asserv_setCoderEntrax(195.0);
    asserv_setCoderStep(0.00849123461395001864975755315181); // 72.5mm wheel
    
    return 0;
}

