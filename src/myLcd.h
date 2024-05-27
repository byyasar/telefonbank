#include <LiquidCrystal_I2cTUR.h>

// LCD2004 adres

#define LCD_ADDR 0x27

LiquidCrystal_I2cTUR    lcd(LCD_ADDR, 20, 4);

void EkraniTemizle()
{
    lcd.clear();
}

// lcd(sütun,satir)
void SatirTemizle(int satir)
{
    lcd.setCursor(0, satir);
    lcd.print("                    ");
    lcd.setCursor(0, satir);
}

void EkranaYaz(int satir, String mesaj)
{
    SatirTemizle(satir);
    lcd.print(mesaj);
}
