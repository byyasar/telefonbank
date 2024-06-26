#include <Wire.h>                 // I2C kütüphanesi
#include <LiquidCrystal_I2cTUR.h> // I2C LCD kütüphanesi
#include <Keypad.h>               // Keypad kütüphanesi
#include "MotorControl.h"
#include "RFIDControl.h"
#include "EncoderControl.h"
#include "lcd.h"      // LCD işlemlerini içeren dosya
#include "mykeypad.h" // Keypad işlemlerini içeren dosya
#include "password.h" // Şifre işlemlerini içeren dosya

LiquidCrystal_I2cTUR lcd(0x27, 20, 4); // I2C adresi 0x27 olan 20x4 LCD tanımlaması

#define onayBtn 4 // telefon yerleştirdikten sonraki buton

extern const int numSections;
extern String sectionPasswords[numSections];
extern String rfidUIDs[numSections];

// Keypad ayarları
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

uint8_t colPins[COLS] = {39, 37, 35, 33}; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = {47, 45, 43, 41}; // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

unsigned long lastActivityTime;              // Son aktivite zamanı
const unsigned long timeoutDuration = 10000; // 10 saniye zaman aşımı süresi
bool inPasswordEntryMode = false;            // Şifre giriş modu durumu
bool inManuelMotorKontrolMode = false;
bool isKapakAcik = false;

int konum = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(onayBtn, INPUT);

  // Pin ve motor ayarları
  setupMotors();
  setupEncoder();

  // LCD ve RFID başlatma
  lcd.init();
  lcd.backlight();
  SPI.begin();
  mfrc522.PCD_Init();

  // Şifre ve RFID UID dizilerini doldurun (örnek)
  for (int i = 0; i < numSections; i++)
  {
    sectionPasswords[i] = String(i); // Her bölme için şifre olarak bölüm numarasını kullanın (örnek)
    rfidUIDs[i] = "";                // Her bölme için sahte UID (örnek)
  }
  rfidUIDs[0] = "3c8305";
  rfidUIDs[9] = "ffde251e";
  rfidUIDs[4] = "69de397d";

  sifirlamaFNC();
  stepperX.setCurrentPosition(0); // Mevcut pozisyonu sıfırla
  encoderCount = 0;               // Enkoder sayısını sıfırla

  Serial.println("Sıfırlama tamamlandı.");

  showWelcomeScreen();         // Hoş geldiniz ekranını göster
  lastActivityTime = millis(); // Son aktivite zamanını güncelle
}

void loop()
{
  if (konum != stepperX.currentPosition())
  {
    Serial.println(stepperX.currentPosition());
    konum = stepperX.currentPosition();
  }

  handleRFID(numSections, rfidUIDs);
  handleSerialCommands();
  // handleKeypad(numSections, sectionPasswords);
  char key = keypad.getKey(); // Tuş durumu oku

  if (key)
  {
    Serial.println(key);
    lastActivityTime = millis(); // Tuşa basıldıysa son aktivite zamanını güncelle
    handleKey(key);              // Tuşu işle
  }

  if (inPasswordEntryMode)
  {
    unsigned long timeLeft = (timeoutDuration - (millis() - lastActivityTime)) / 1000; // Kalan süreyi hesapla
    if (timeLeft > 0)
    {
      showCountdown(timeLeft); // Kalan süreyi göster
    }
    else
    {
      showWelcomeScreen(); // Zaman aşımı olduysa hoş geldiniz ekranını göster
    }
  }

  if (digitalRead(onayBtn)==1&& isKapakAcik)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kapak kapanıyor");
    lcd.setCursor(0,1);
    lcd.print("Lütfen bekleyin");
    cekmeceIceriFnc();
    kapagiKapatFnc();
     delay(2000); // 2 saniye bekle
    showWelcomeScreen(); // Hoş geldiniz ekranını göster
    isKapakAcik=false;
  }
  
}

void handleSerialCommands()
{
  if (Serial.available() > 0)
  {
    char command = Serial.read();
    switch (command)
    {
    case 'a':
      sagaDonFnc();
      Serial.println("Tam tur ileri");
      break;
    case 's':
      solaDonFnc();
      Serial.println("Tam tur geri");
      break;
    case 'c':
      Serial.println("Motor durduruldu");
      stepperX.stop(); // Motoru durdur
      stepperY.stop(); // Motoru durdur
      stepperZ.stop(); // Motoru durdur
      digitalWrite(enablePinX, 1);
      digitalWrite(enablePinY, 1);
      digitalWrite(enablePinZ, 1);
      break;
    case 'z':
      Serial.println("Çekmeceyi kapat");
      cekmeceDisariFnc();
      break;
    case 'x':
      Serial.println("Çekmeceyi aç");
      cekmeceIceriFnc();
      break;
    case 'm':
      Serial.println("Kapağı aç");
      kapagiAcFnc();
      break;
    case 'n':
      Serial.println("Kapağı kapat");
      kapagiKapatFnc();
      break;
    default:
      Serial.println("Geçersiz komut");
      break;
    }
  }
}
