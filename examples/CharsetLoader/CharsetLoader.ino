// Do not remove the include below
#include "max7456.h"
#include <SPI.h>

//THIS ARRAY IS OBTAINED BY AN OTHER PROGRAM
//Those 13.5ko of data are stored in the program memory.
//Be awared that 0xFF are stored as 0x55 as program memory can't stand series of 0xFF (Arduino vicious problem)
#include "charset.h"

Max7456 osd;

void setup() {
  //Sample code : Write a complete table of character in the character memory of the max7456.

  charact currentChar; //represents a character as stored in memory (byte[54])

  Serial.begin(9600);
  SPI.begin();
  Serial.println(F("Initializing..."));
  osd.init(6);
  Serial.println(F("Updating MAX7456 charset"));
  Serial.println(F("Are you sure? (y/n)"));
  bool goodChar = false;

  osd.activateOSD(false); // Deactivate osd display.
  //Just some serial manipulations
  while (!goodChar) {
    while (!Serial.available())
      ;
    char found;
    found = char(Serial.read());
    goodChar = (found == 'y' || found == 'Y');
    if (found == 'n' || found == 'N') {
      Serial.println(F("------ NOTHING DONE ------"));
      Serial.println(F("please unplug your arduino"));
      while (true)
        ;
    }
  }

  char number[] = "000";

  for (int i = 0; i <= 0xff; i++) {
    Serial.print(F("Inserting "));
    dtostrf(i, 3, 0, number);
    Serial.print(number);
    Serial.println(F(" of 255"));
    Max7456::getCARACFromProgMem(
        tableOfAllCharacters, i,
        currentChar); //Because the table is too big for ram memory
    osd.sendCharacter(currentChar, i & 0x0f, (i & 0xf0) >> 4);

    for (int j = 0; j < 19; j++) //Rewind Serial.
      Serial.print(char(0x08));
  }
  Serial.println(F("---------- DONE! ----------"));
  Serial.println(F("please unplug your arduino."));
}

void loop() {
  //Nothing done here
}
