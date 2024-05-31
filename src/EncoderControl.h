#ifndef ENCODERCONTROL_H
#define ENCODERCONTROL_H

// Enkoder pin
int encoderPin=2;

// Enkoder için değişkenler
volatile long encoderCount = 0;

void setupEncoder() {
    pinMode(encoderPin, INPUT_PULLUP);
}

void encoderISR() {
    encoderCount++;
}

#endif
