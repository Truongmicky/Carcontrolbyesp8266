#include "Motor.h"
#include "Config.h"
// Khoi tao chan ra vao
void motorInit(){
    pinMode(PIN_INT1, OUTPUT);
    pinMode(PIN_INT2, OUTPUT);
    pinMode(PIN_INT3, OUTPUT);
    pinMode(PIN_INT4, OUTPUT);
    pinMode(PIN_ENA, OUTPUT);
    pinMode(PIN_ENB, OUTPUT);
    motorStop();
}

// Khoi tao motor
void motorForward(uint8_t speed){
    digitalWrite(PIN_INT1, HIGH);
    digitalWrite(PIN_INT2, LOW);
    digitalWrite(PIN_INT3, HIGH);
    digitalWrite(PIN_INT4, LOW);
    analogWrite(PIN_ENA, speed);
    analogWrite(PIN_ENB, speed);
}

void motorBackward(uint8_t speed){
    digitalWrite(PIN_INT1, LOW);
    digitalWrite(PIN_INT2, HIGH);
    digitalWrite(PIN_INT3, LOW);
    digitalWrite(PIN_INT4, HIGH);
    analogWrite(PIN_ENA, speed);
    analogWrite(PIN_ENB, speed);
}

void motorLeft(uint8_t speed){
    digitalWrite(PIN_INT1, LOW);
    digitalWrite(PIN_INT2, HIGH);
    digitalWrite(PIN_INT3, LOW);
    digitalWrite(PIN_INT4, HIGH);
    analogWrite(PIN_ENA, 0);
    analogWrite(PIN_ENB, speed);
}

void motorRight(uint8_t speed){
    digitalWrite(PIN_INT1, LOW);
    digitalWrite(PIN_INT2, HIGH);
    digitalWrite(PIN_INT3, LOW);
    digitalWrite(PIN_INT4, HIGH);
    analogWrite(PIN_ENA, speed);
    analogWrite(PIN_ENB, 0);
}

void motorStop(){
    digitalWrite(PIN_INT1, LOW);
    digitalWrite(PIN_INT2, LOW);
    digitalWrite(PIN_INT3, LOW);
    digitalWrite(PIN_INT4, LOW);
    analogWrite(PIN_ENA, 0);
    analogWrite(PIN_ENB, 0);
}