#include <AccelStepper.h>
#include "myLcd.h"
#include "myGlobalDegiskenler.h"





// AccelStepper nesnesi oluşturun
AccelStepper stepperX(1, stepPinX, dirPinX);  // 1: Driver control interface
AccelStepper stepperY(1, stepPinY, dirPinY);  // 1: Driver control interface
AccelStepper stepperZ(1, stepPinZ, dirPinZ);  // 1: Driver control interface


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
    //geri dön
    int fark = a - id;
    stepperX.moveTo(-(stepperX.currentPosition() - (motor1Step * fark)));
  } else {
    //ileri dön
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


void motor2SagaDonFnc() {

  stepperY.setCurrentPosition(0);
  digitalWrite(enablePinY, 0);
  stepperY.setSpeed(800);
  stepperY.setAcceleration(1000);
  stepperY.moveTo(stepperY.currentPosition() + motor2Step);
  while (stepperY.distanceToGo() != 0) {
    stepperY.runSpeed();
  }
  digitalWrite(enablePinY, 1);
  cekmeceDurum=false;
}


void motor2SolaDonFnc() {


  digitalWrite(enablePinY, 0);
  stepperY.setAcceleration(1000);
  stepperY.setSpeed(800);
  stepperY.moveTo(stepperY.currentPosition() - motor2Step);
  while (stepperY.distanceToGo() != 0) {
    stepperY.runSpeed();
  }
  digitalWrite(enablePinY, 1);
  cekmeceDurum=true;
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
  //  stepperX.setCurrentPosition(0);
  stepperX.moveTo(stepperX.currentPosition() - motor1Step);
  while (stepperX.distanceToGo() != 0) {
    stepperX.run();
  }
  digitalWrite(enablePinX, 1);
}


void sifirlamaFNC() {
  Serial.println("Sıfırlama başladı");
  EkranaYaz(0,"Cihaz Hazirlaniyor");
  stepperX.setCurrentPosition(0);
  stepperX.moveTo(stepperX.currentPosition() + 89000);  // Geri hareket et
  stepperX.setAcceleration(1000);
  //stepperX.setSpeed(400);
  digitalWrite(enablePinX, 0);
  while (digitalRead(encoderPin) == 1) {
    stepperX.run();
  }
  digitalWrite(enablePinX, 1);
}




void motor3SagaDonFnc() {
  stepperZ.setCurrentPosition(0);
  digitalWrite(enablePinZ, 0);
  stepperZ.setMaxSpeed(200000);
  stepperZ.setAcceleration(4000);
  stepperZ.moveTo(stepperZ.currentPosition() + motor3Step);
  while (stepperZ.distanceToGo() != 0) {
    stepperZ.run();
  }
  digitalWrite(enablePinZ, 1);
  kapakDurum=true;
}


void motor3SolaDonFnc() {
  digitalWrite(enablePinZ, 0);
  stepperZ.setMaxSpeed(200000);
  stepperZ.setAcceleration(4000);
  stepperZ.moveTo(stepperZ.currentPosition() - motor3Step);
  while (stepperZ.distanceToGo() != 0) {
    stepperZ.run();
  }
  digitalWrite(enablePinZ, 1);
  kapakDurum=false;
}
