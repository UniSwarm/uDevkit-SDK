/**
 * @file sharp_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date avril 28, 2016, 13:34  
 * 
 * @brief Conversion functions for Sharp analog sharp_distance sensor
 */
 
 #include "sharp.h"
 
 #define MAX_VALUE 13

const uint16_t sharp_tensionLFP[MAX_VALUE] =  \
{852,787,620,474,381,465,279,248,226, 201, 186, 170, 130};
const uint16_t sharp_distanceLFP[MAX_VALUE] = \
{150,200,300,400,500,600,700,800,900,1000,1100,1200,1500};
uint16_t sharp_longfarSharp(uint16_t v)
{
    unsigned char i;
    float d;
 
    if(v>sharp_tensionLFP[0] || v<sharp_tensionLFP[MAX_VALUE-1]) return 9999;
    for(i=1;i<MAX_VALUE-1;i++) if(v>sharp_tensionLFP[i]) break;
    d=sharp_distanceLFP[i]-(float)((sharp_distanceLFP[i]-sharp_distanceLFP[i-1]))/(float)((sharp_tensionLFP[i-1]-sharp_tensionLFP[i]))*(float)(v-sharp_tensionLFP[i]);
    return (uint16_t)d;
}

const uint16_t sharp_tensionLP[MAX_VALUE] =  \
{977,924,853,713,508,406,335,288,229,189,161,136,90};
const uint16_t sharp_distanceLP[MAX_VALUE] = \
{ 60, 70, 80,100,150,200,250,300,400,500,600,700,800};
uint16_t sharp_farSharp(uint16_t v)
{
    unsigned char i;
    float d;
 
    if(v>sharp_tensionLP[0] || v<sharp_tensionLP[MAX_VALUE-1]) return 9999;
    for(i=1;i<MAX_VALUE-1;i++) if(v>sharp_tensionLP[i]) break;
    d=sharp_distanceLP[i]-(float)((sharp_distanceLP[i]-sharp_distanceLP[i-1]))/(float)((sharp_tensionLP[i-1]-sharp_tensionLP[i]))*(float)(v-sharp_tensionLP[i]);
    return (uint16_t)d;
}

const uint16_t sharp_tensionCP[MAX_VALUE] =  \
{946,930,849,729,651,546,487,434,397,357,285,167,102};
const uint16_t sharp_distanceCP[MAX_VALUE] = \
{ 30, 35, 40, 50, 60, 70, 80, 90,100,120,140,250,400};
uint16_t sharp_nearSharp(uint16_t v)
{
    unsigned char i;
    float d;
 
    if(v>sharp_tensionCP[0] || v<sharp_tensionCP[MAX_VALUE-1]) return 9999;
    for(i=1;i<MAX_VALUE-1;i++) if(v>sharp_tensionCP[i]) break;
    d=sharp_distanceCP[i]-(float)((sharp_distanceCP[i]-sharp_distanceCP[i-1]))/(float)((sharp_tensionCP[i-1]-sharp_tensionCP[i]))*(float)(v-sharp_tensionCP[i]);
    return (uint16_t)d;
}

uint16_t sharp_convert(uint16_t v, uint8_t type)
{
    switch(type)
    {
        case Voltage:
            return v;
        case NearSharp:
            return sharp_nearSharp(v);
        case FarSharp:
            return sharp_farSharp(v);
        case LongFarSharp:
            return sharp_longfarSharp(v);
    }
    return v;
}
