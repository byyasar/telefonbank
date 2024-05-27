#include <Arduino.h>
#include <MFRC522.h>
#include "myPins.h"
#include "motorFnc.h"


// RFID ve LCD nesneleri oluşturun
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Bölme ve şifre dizisi
const int numSections = 72;

String sectionPasswords[numSections];
String rfidUIDs[numSections];

// Şifre doğrulama fonksiyonu
bool validatePassword(int section, String input)
{
    return input == sectionPasswords[section];
}

// RFID doğrulama fonksiyonu
bool validateRFID(int section, String uid)
{
    return uid == rfidUIDs[section];
}

/*
  // Şifre ve RFID UID dizilerini doldurun (örnek)
  for (int i = 0; i < numSections; i++) {
    sectionPasswords[i] = String(i);  // Her bölme için şifre olarak bölüm numarasını kullanın (örnek)
    rfidUIDs[i] = "";                 // Her bölme için sahte UID (örnek)
  }



  rfidUIDs[0] = "3c8305";
  rfidUIDs[9] = "ffde251e";
  rfidUIDs[4] = "69de397d";

*/

// RFID kart okuma

void RfidOkumaFnc()
{

    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
    {
        String uid = "";
        for (byte i = 0; i < mfrc522.uid.size; i++)
        {
            uid += String(mfrc522.uid.uidByte[i], HEX);
        }
        Serial.print("UID okundu: ");
        Serial.println(uid);

        for (int i = 0; i < numSections; i++)
        {
            if (validateRFID(i, uid))
            {
                Serial.print(i);
                Serial.println("Doğrulandı");
                konumaGitFnc(i);
                break;
            }
        }
        mfrc522.PICC_HaltA();
    }
}
