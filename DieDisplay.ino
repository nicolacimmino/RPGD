//  Copyright (C) 2019 Nicola Cimmino
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include <SSD1306AsciiAvrI2c.h>

#define DISPLAY_I2C_ADDRESS 0x3C

SSD1306AsciiAvrI2c oled;

extern uint8_t counter;

void displaySetup() {
    oled.begin(&Adafruit128x64, DISPLAY_I2C_ADDRESS);    
}

void displayRefresh() {
    printHeader();
    printResult();
}

/**
 * Print the header contiaining the modes flags indicators.
 */
void printHeader()
{
    oled.setCursor(0, 0);
    oled.setFont(System5x7);
    oled.set1X();
    oled.print("1x D100 +0");
    if(!highVoltageReserviourGood) {
        oled.print(" CHG");
    }
    oled.clearToEOL();
}


void printResult()
{    
    oled.setCursor(0, 3);
    oled.set2X();
    String counterString = String("000");
    counterString.concat(String(counter));
    counterString = counterString.substring(counterString.length() - 3);
    oled.setFont(lcdnums12x16);
    oled.setCol(24);
    oled.print(counterString);
}