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

#include "DieDisplay.h"
#include <SSD1306AsciiAvrI2c.h>

#define PIN_ENC_A 10
#define PIN_ENC_B 11
#define PIN_ENC_SW 12
#define DISPLAY_I2C_ADDRESS 0x3C

uint8_t counter;

DieDisplay *dieDisplay;
SSD1306AsciiAvrI2c *oled;

void setup()
{    
    pinMode(PIN_ENC_A, INPUT_PULLUP);
    pinMode(PIN_ENC_B, INPUT_PULLUP);
    pinMode(PIN_ENC_SW, INPUT_PULLUP);
        
    setupRotaryEncoder();

    initChargePump();
    Serial.begin(115200);    

    oled = new SSD1306AsciiAvrI2c();
    oled->begin(&Adafruit128x64, DISPLAY_I2C_ADDRESS);

    dieDisplay = new DieDisplay(oled);
    dieDisplay->SetTitle((char*)"My Test");    
}

void loop()
{
    uint8_t throws[5] = {50, 12, 22, 34, 99};
    
    for(int ix=1; ix<6; ix++) {
        dieDisplay->ShowResults(ix, throws);
        delay(1000);
    }
    
    // if(!isHighVoltageReseviourAboveMin()) {
    //     displayRefresh();
    //     chargeHighVoltageReserviour();
    // }

    // encoderScanKey();
    // displayRefresh();
    // Serial.println(analogRead(A0));
}

void onEncoderLongKeyPress() {
    counter = 99;
    //displayRefresh();
}

void onEncoderKeyPress() {
    counter = random(1, 10);   
    //displayRefresh();
}

void onEncoderRotation(bool cwRotation) {
    counter += cwRotation ? 1 : -1;
}