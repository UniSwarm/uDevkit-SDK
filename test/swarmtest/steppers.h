

#ifndef STEPPERS_H
#define STEPPERS_H

void steppers_init();

void steppers_stop();
void steppers_start();

void steppers_setSpeed(int16_t speed);

#endif // STEPPERS_H