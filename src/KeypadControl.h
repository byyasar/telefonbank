/*#ifndef KEYPADCONTROL_H
#define KEYPADCONTROL_H

#include <Keypad.h>

// Keypad ayarları
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 39, 37, 35, 33 };  // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 47, 45, 43, 41 };  // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

bool validatePassword(int section, String input) {
    return input == sectionPasswords[section];
}

void handleKeypad(int numSections, String sectionPasswords[]) {
    char key = keypad.getKey();
    if (key) {
        static String input = "";
        if (key == '#') {
            for (int i = 0; i < numSections; i++) {
                if (validatePassword(i, input)) {
                    moveToSection(i);
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Bölme: ");
                    lcd.print(i);
                    lcd.setCursor(0, 1);
                    lcd.print("Sifre Gecis Tamam");
                    delay(2000);
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Komut Bekleniyor");
                    break;
                }
            }
            input = "";
        }
        if (key == 'A') { motor2SagaDonFnc(); }
        if (key == 'B') { motor2SolaDonFnc(); }
        if (key == 'C') { motor3SolaDonFnc(); }
        if (key == 'D') {
            motor3SagaDonFnc();
        } else {
            input += key;
            lcd.setCursor(0, 1);
            lcd.print("Sifre: ");
            lcd.print(input);
        }
    }
}

#endif

*/
