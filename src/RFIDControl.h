#ifndef RFIDCONTROL_H
#define RFIDCONTROL_H

#include <SPI.h>
#include <MFRC522.h>
#include "MotorControl.h"




// Değişkenler ve sabitler
const int numSections = 72;
String sectionPasswords[numSections];
String rfidUIDs[numSections];


// RFID pinleri
#define SS_PIN 53
#define RST_PIN 49

MFRC522 mfrc522(SS_PIN, RST_PIN);

bool validateRFID(int section, String uid) {
    return uid == rfidUIDs[section];
}

void handleRFID(int numSections, String rfidUIDs[]) {
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        String uid = "";
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            uid += String(mfrc522.uid.uidByte[i], HEX);
        }
        Serial.print("UID okundu: ");
        Serial.println(uid);

        for (int i = 0; i < numSections; i++) {
            if (validateRFID(i, uid)) {
                Serial.print(i);
                Serial.println("Doğrulandı");
                konumaGitFnc(i);
                break;
            }
        }
        mfrc522.PICC_HaltA();
    }
}

#endif
