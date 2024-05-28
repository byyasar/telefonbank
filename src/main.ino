// 27.5.24
#include <Arduino.h>
#include <Wire.h>
#include "myKeypad.h"
#include "myRfid.h"

String satir1, satir2, satir3, satir4 = "";

ulong sonZaman = 0;
ulong ekranYenileme = 500;

void setup()
{
  Serial.begin(9600);

  // Motor1 pin ayarları
  pinMode(dirPinX, OUTPUT);
  pinMode(stepPinX, OUTPUT);
  pinMode(enablePinX, OUTPUT);
  // Motor2 pin ayarları
  pinMode(dirPinY, OUTPUT);
  pinMode(stepPinY, OUTPUT);
  pinMode(enablePinY, OUTPUT);
  // Motor3 pin ayarları
  pinMode(dirPinZ, OUTPUT);
  pinMode(stepPinZ, OUTPUT);
  pinMode(enablePinZ, OUTPUT);
  // Motoru etkinleştir
  digitalWrite(enablePinX, 1);
  digitalWrite(enablePinY, 1);
  digitalWrite(enablePinZ, 1);

  // Enkoder pinini giriş olarak ayarla
  pinMode(encoderPin, INPUT_PULLUP);

  // Motorun hız ve ivme ayarları
  stepperX.setMaxSpeed(1000);
  stepperX.setAcceleration(500);

  // LCD ve RFID başlatma
  lcd.init();
  lcd.backlight();
  SPI.begin();
  mfrc522.PCD_Init();

  sifirlamaFNC();
  stepperX.setCurrentPosition(0); // Mevcut pozisyonu sıfırla
  Serial.println("Sıfırlama tamamlandı.");
  satir1 = "   Telefon Bank v1";
  satir2 = "--- Hoş Geldiniz ---";
  satir3 = "";
  satir4 = ".. Kart Okutunuz ...";
}

void loop()
{

  EkraniGuncelleFnc();
  KlayeOkumaFnc();
  if (konum != stepperX.currentPosition())
  {
    Serial.println(stepperX.currentPosition());
    konum = stepperX.currentPosition();
  }

  // Keypad okuma
  char key = keypad.getKey();
  if (key)
  {
    static String input = "";
    if (key == '#')
    {

      satir1 = "Şifre Giriniz :";
      satir2 = "";
      satir3 = "";
      satir4 = "";
      lcd.setCursor(0, 3);
      satir3 = girilenSifre;
      // Şifreyi sıfırlama
      memset(girilenSifre, 0, sizeof(girilenSifre));
      sifreIndex = 0;
    }
    else if (sifreIndex < 6)
    {
      // Şifre girişi devam ediyor
      girilenSifre[sifreIndex] = key;
      sifreIndex++;
      satir3 = girilenSifre;
      if (key == 'C')
      {
        // şifreyi temizle
        Serial.println("şifreyi temizle");
        for (int i = 0; i < 6; i++)
        {
          girilenSifre[i] =' ';
        }
        satir3 = girilenSifre;
      }
    }
    if (key == '*' && sifreIndex == 6)
    {
      
      if (key == 'C')
      {
        // şifreyi temizle
        Serial.println("şifreyi temizle");
        for (int i = 0; i < 6; i++)
        {
          girilenSifre[i] =' ';
        }
        satir3 = girilenSifre;
      }
      Serial.println("şifreyi kontrol et");
      int id = (String(girilenSifre[0]) + String(girilenSifre[1])).toInt();

      // char str[4];
      String sifre = "";
      for (int i = 2; i < 6; i++)
      {
        // sprintf(str, "%d", girilenSifre[i]);
        // itoa(girilenSifre[i], str, 10); // 10 tabanı (decimal) kullanarak dönüştür
        sifre += String(girilenSifre[i]);

        Serial.print("sifre :");
        Serial.println(sifre);
      }
      Serial.print("sifre :");
      Serial.println(sifre);
      Serial.print("id :");
      Serial.println(sifreDogrulamaFnc(id, sifre));
    }
    if (key == 'A')
    {
      motor2SagaDonFnc();
    }
    if (key == 'B')
    {
      motor2SolaDonFnc();
    }
    /*if (key == 'C')
    {
      motor3SolaDonFnc();
    }*/
    if (key == 'D')
    {
      motor3SagaDonFnc();
    }
  }
}

void EkraniGuncelleFnc()
{
  String mesaj = "";
  cekmeceDurum ? mesaj = "Çek:Açık" : mesaj = "Çek:Kapalı";
  kapakDurum ? mesaj += " Kap:Açık" : mesaj += " Kap:Kapal";
  satir4 = mesaj;

  if (millis() - sonZaman > ekranYenileme)
  {
    EkranaYaz(0, satir1);
    EkranaYaz(1, satir2);
    EkranaYaz(2, satir3);
    EkranaYaz(3, satir4);
    sonZaman = millis();
  }
}

void KlayeOkumaFnc()
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
      stepperX.stop(); // Motoru durdur
      stepperY.stop(); // Motoru durdur
      stepperZ.stop(); // Motoru durdur
      digitalWrite(enablePinX, 1);
      digitalWrite(enablePinY, 1);
      digitalWrite(enablePinZ, 1);
      Serial.println("Motor durduruldu");
      break;

    case 'z':
      motor2SagaDonFnc();
      Serial.println("2-Tam tur ileri");
      break;
    case 'x':
      motor2SolaDonFnc();
      Serial.println("2-Tam tur geri");
      break;
    case 'm':
      motor3SagaDonFnc();
      Serial.println("3-Tam tur ileri");
      break;
    case 'n':
      motor3SolaDonFnc();
      Serial.println("3-Tam tur geri");
      break;
    default:

      Serial.println("Geçersiz komut");
      break;
    }
  }
}