#include <Arduino.h>
#include <MFRC522.h>
#include "myPins.h"
#include "motorFnc.h"


// RFID ve LCD nesneleri oluşturun
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Bölme ve şifre dizisi
const int numSections = 72;

//String sectionPasswords[numSections];
String rfidUIDs[numSections];

const char* sifreler[72] = {
  "1234", "2345", "3456", "4567", "5678", "6789", "7890", "8901",
  "9012", "0123", "1111", "2222", "3333", "4444", "5555", "6666",
  "7777", "8888", "9999", "0000", "1357", "2468", "3690", "4812",
  "5923", "6034", "7145", "8256", "9367", "1478", "2589", "3691",
  "4702", "5813", "6924", "7035", "8146", "9257", "0368", "1479",
  "2580", "3692", "4703", "5814", "6925", "7036", "8147", "9258",
  "0369", "1470", "2581", "3693", "4704", "5815", "6926", "7037",
  "8148", "9259", "0360", "1471", "2582", "3694", "4705", "5816",
  "6927", "7038", "8149", "9250", "0361", "1472", "2583", "3695"
};

// Şifre doğrulama fonksiyonu
bool sifreDogrulamaFnc(int section, String input)
{
    return input == sifreler[section];
}

// RFID doğrulama fonksiyonu
bool RFIDDogrulamaFnc(int section, String uid)
{
    return uid == rfidUIDs[section];
}


void rfidKartlariOlusturFnc(){
  // Şifre ve RFID UID dizilerini doldurun (örnek)
  for (int i = 0; i < numSections; i++) {
    sifreler[i] = "";                  
    rfidUIDs[i] = "";                 
  }


  rfidUIDs[0] = "3c8305";
  rfidUIDs[9] = "ffde251e";
  rfidUIDs[4] = "69de397d";




}


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
            if (RFIDDogrulamaFnc(i, uid))
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
