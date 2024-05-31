#include "password.h"
#include "lcd.h"
#include "MotorControl.h"

extern LiquidCrystal_I2cTUR lcd; // LCD nesnesi

char enteredPassword[7];                  // Girilen şifre için dizi
byte passwordIndex = 0;                   // Şifre dizisinin indeksi
const char correctPassword[7] = "336699"; // Doğru şifre

extern bool inPasswordEntryMode; // Şifre giriş modu durumu
extern bool isKapakAcik;

void verifyPassword()
{
  enteredPassword[6] = '\0'; // Şifre dizisini null ile sonlandır
  if (strcmp(enteredPassword, correctPassword) == 0)
  {
    lcd.clear();               // LCD'yi temizle
    lcd.setCursor(0, 1);       // İkinci satıra git
    lcd.print("Sifre dogru!"); // "Şifre doğru!" yazısını yaz
    konumaGitFnc(3);
    lcd.clear();            // LCD'yi temizle
    lcd.setCursor(0, 1);    // İkinci satıra git
    lcd.print("Calışıyor"); // "Şifre doğru!" yazısını ya
    kapagiAcFnc();
    cekmeceDisariFnc();
    isKapakAcik = true;
  }
  else
  {
    lcd.clear();                // LCD'yi temizle
    lcd.setCursor(0, 1);        // İkinci satıra git
    lcd.print("Sifre yanlis!"); // "Şifre yanlış!" yazısını yaz
  }
  delay(2000);         // 2 saniye bekle
  showWelcomeScreen(); // Hoş geldiniz ekranını göster
}
