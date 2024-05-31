#include "lcd.h"
#include <LiquidCrystal_I2cTUR.h>

extern LiquidCrystal_I2cTUR lcd;    // LCD nesnesi
extern bool inPasswordEntryMode; // Şifre giriş modu durumu


void lcdInit()
{
    lcd.init();      // LCD'yi başlat
    lcd.backlight(); // LCD arka ışığını aç
    
}


void showHomingScreen()
{
    lcd.clear();                  // LCD'yi temizle
    lcd.setCursor(2, 0);          // İlk satıra git
    lcd.print("- Telefon Bank -");     // "Hoşgeldiniz" yazısını yaz
    lcd.setCursor(0, 1);          // İkinci satıra git
    lcd.print("Makina Başlatılıyor"); // "# ile şifre gir" yazısını yaz
    lcd.setCursor(7, 2);          // İkinci satıra git
    lcd.print("-----"); // "# ile şifre gir" yazısını yaz
    lcd.setCursor(1,3);          // İkinci satıra git
    lcd.print("Lütfen bekleyin."); // "# ile şifre gir" yazısını yaz
   
}

void showWelcomeScreen()
{
    lcd.clear();                  // LCD'yi temizle
    lcd.setCursor(4, 0);          // İlk satıra git
    lcd.print("Hoşgeldiniz");     // "Hoşgeldiniz" yazısını yaz
    lcd.setCursor(1, 1);          // İkinci satıra git
    lcd.print("# ile şifre girin"); // "# ile şifre gir" yazısını yaz
    lcd.setCursor(7, 2);          // İkinci satıra git
    lcd.print("veya"); // "# ile şifre gir" yazısını yaz
    lcd.setCursor(1,3);          // İkinci satıra git
    lcd.print("Kartınızı okutun."); // "# ile şifre gir" yazısını yaz
    passwordIndex = 0;            // Şifre dizisi indeksini sıfırla
    inPasswordEntryMode = false;  // Şifre giriş modunu kapat
}

void showPasswordScreen()
{
    lcd.clear();                     // LCD'yi temizle
    lcd.setCursor(0, 0);             // İlk satıra git
    lcd.print("Şifrenizi Giriniz:"); // "Şifrenizi giriniz:" yazısını yaz
    lcd.setCursor(7, 1);             // Üçüncü satıra git
    inPasswordEntryMode = true;      // Şifre giriş modunu aç
    lcd.print("______"); 
    lcd.setCursor(0, 3); 
    lcd.print("Sil->C, Onay->D ");
    

}

void showCountdown(unsigned long seconds)
{
    lcd.setCursor(18, 3); // Dördüncü satırın en sağına git
    if (seconds < 10)
    {
        lcd.print(" "); // Tek haneli sayıların hizalaması için boşluk ekle
    }
    lcd.print(seconds); // Kalan saniyeyi yazdır
}
