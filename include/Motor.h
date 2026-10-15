#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

void motorInit();
void motorForward(uint8_t speed);
void motorBackward(uint8_t speed);
void motorLeft(uint8_t speed);
void motorRight(uint8_t speed);
void motorStop();

#endif
