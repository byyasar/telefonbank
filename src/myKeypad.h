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
