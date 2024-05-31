#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <AccelStepper.h>
#include "lcd.h"


extern int konum;
extern int encoderPin;



// Motor1 pinleri
int motor1Step = 890;
#define dirPinX A1
#define stepPinX A0
#define enablePinX 38

// Motor2 pinleri
int motor2Step = 325;
#define dirPinY A7
#define stepPinY A6
#define enablePinY A2

// Motor3 pinleri
int motor3Step = 20000;
#define dirPinZ 48
#define stepPinZ 46
#define enablePinZ A8

// Motorun adım sayısı ve mikrostep ayarı
const int stepsPerRevolution = 200;                                   // Motorun adım sayısı (1.8 derece/adım)
const int microsteps = 16;                                            // Mikrostep ayarı
const int stepsPerDivision = (stepsPerRevolution * microsteps) / 72;  // 72 bölmeli diskin bir bölmesi için adım sayısı

// AccelStepper nesneleri
AccelStepper stepperX(1, stepPinX, dirPinX);
AccelStepper stepperY(1, stepPinY, dirPinY);
AccelStepper stepperZ(1, stepPinZ, dirPinZ);

void setupMotors() {
    pinMode(dirPinX, OUTPUT);
    pinMode(stepPinX, OUTPUT);
    pinMode(enablePinX, OUTPUT);

    pinMode(dirPinY, OUTPUT);
    pinMode(stepPinY, OUTPUT);
    pinMode(enablePinY, OUTPUT);

    pinMode(dirPinZ, OUTPUT);
    pinMode(stepPinZ, OUTPUT);
    pinMode(enablePinZ, OUTPUT);

    digitalWrite(enablePinX, 1);
    digitalWrite(enablePinY, 1);
    digitalWrite(enablePinZ, 1);

    stepperX.setMaxSpeed(1000);
    stepperX.setAcceleration(2000);
}

void moveToSection(int section) {
    long targetPosition = section * stepsPerDivision;
    stepperX.moveTo(targetPosition);
    while (stepperX.distanceToGo() != 0) {
        stepperX.run();
    }
}

void konumaGitFnc(int id) {
    Serial.print("cuurent pos:");
    Serial.println(stepperX.currentPosition());
    Serial.print("id:");
    Serial.println(id);

    digitalWrite(enablePinX, 0);
    stepperX.setSpeed(400);
    stepperX.setAcceleration(400);
    int a = konum / motor1Step;
    if (a > id) {
        int fark = a - id;
        stepperX.moveTo(-(stepperX.currentPosition() - (motor1Step * fark)));
    } else {
        int fark = (id - a);
        stepperX.moveTo(-(stepperX.currentPosition() + (motor1Step * fark)));
    }

    while (stepperX.distanceToGo() != 0) {
        stepperX.run();
    }
    digitalWrite(enablePinX, 1);
    Serial.print("cuurent pos:");
    Serial.println(stepperX.currentPosition());
}

void cekmeceIceriFnc() {
    stepperY.setCurrentPosition(0);
    digitalWrite(enablePinY, 0);
    stepperY.setSpeed(1500);
    stepperY.setAcceleration(1000);
    stepperY.moveTo(stepperY.currentPosition() + motor2Step);
    while (stepperY.distanceToGo() != 0) {
        stepperY.runSpeed();
    }
    digitalWrite(enablePinY, 1);
}

void cekmeceDisariFnc()  {
    digitalWrite(enablePinY, 0);
    stepperY.setAcceleration(1000);
    stepperY.setSpeed(3000);
    stepperY.moveTo(stepperY.currentPosition() - motor2Step);
    while (stepperY.distanceToGo() != 0) {
        stepperY.runSpeed();
    }
    digitalWrite(enablePinY, 1);
}

void sagaDonFnc() {
    digitalWrite(enablePinX, 0);
    stepperX.setSpeed(400);
    stepperX.setAcceleration(400);
    stepperX.moveTo(stepperX.currentPosition() + motor1Step);
    while (stepperX.distanceToGo() != 0) {
        stepperX.run();
    }
    digitalWrite(enablePinX, 1);
}

void solaDonFnc() {
    digitalWrite(enablePinX, 0);
    stepperX.setSpeed(400);
    stepperX.setAcceleration(400);
    stepperX.moveTo(stepperX.currentPosition() - motor1Step);
    while (stepperX.distanceToGo() != 0) {
        stepperX.run();
    }
    digitalWrite(enablePinX, 1);
}

void sifirlamaFNC() {
    Serial.println("Sıfırlama başladı");
    showHomingScreen();
    stepperX.setCurrentPosition(0);
    stepperX.moveTo(stepperX.currentPosition() + 89000);  // Geri hareket et
    stepperX.setAcceleration(1000);
    digitalWrite(enablePinX, 0);
    while (digitalRead(encoderPin) == 1) {
        stepperX.run();
    }
    digitalWrite(enablePinX, 1);
}

void kapagiAcFnc() {
    stepperZ.setCurrentPosition(0);
    digitalWrite(enablePinZ, 0);
    stepperZ.setMaxSpeed(200000);
    stepperZ.setAcceleration(4000);
    stepperZ.moveTo(stepperZ.currentPosition() + motor3Step);
    while (stepperZ.distanceToGo() != 0) {
        stepperZ.run();
    }
    digitalWrite(enablePinZ, 1);
}

void kapagiKapatFnc() {
    digitalWrite(enablePinZ, 0);
    stepperZ.setMaxSpeed(200000);
    stepperZ.setAcceleration(4000);
    stepperZ.moveTo(stepperZ.currentPosition() - motor3Step);
    while (stepperZ.distanceToGo() != 0) {
        stepperZ.run();
    }
    digitalWrite(enablePinZ, 1);
}

#endif
