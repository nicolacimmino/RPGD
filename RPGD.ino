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

#include "Hardware.h"
#include "DieDisplay.h"
#include "DiceThrow.h"
#include "RPGDConfiguration.h"
#include <SSD1306AsciiAvrI2c.h>
#include <EEPROM.h>

uint8_t counter;

DieDisplay *dieDisplay;
SSD1306AsciiAvrI2c *oled;
RPGDConfiguation *configuration;
uint8_t currentThrowConfigurationIndex;
DiceThrow *currentDiceThrow;

void setup()
{
    // EEPROM.write(0, 4);
    // EEPROM.write(1, 6);

    // EEPROM.write(2, 5);
    // EEPROM.write(3, 10);

    // EEPROM.write(4, 0);
    // EEPROM.write(5, 0);

    pinMode(PIN_ENC_A, INPUT_PULLUP);
    pinMode(PIN_ENC_B, INPUT_PULLUP);
    pinMode(PIN_ENC_SW, INPUT_PULLUP);

    setupRotaryEncoder();

    initChargePump();
    Serial.begin(115200);

    oled = new SSD1306AsciiAvrI2c();
    oled->begin(&Adafruit128x64, DISPLAY_I2C_ADDRESS);

    dieDisplay = new DieDisplay(oled);

    configuration = new RPGDConfiguation();

    currentThrowConfigurationIndex = 0;
}

void loop()
{
   encoderScanKey(); 
    
    // uint8_t throws[5] = {50, 12, 22, 34, 99};

    // for (int ix = 1; ix < 6; ix++)
    // {
    //     dieDisplay->ShowResults(ix, throws);
    //     delay(1000);
    // }

    //delete diceThrow;

    // if(!isHighVoltageReseviourAboveMin()) {
    //     displayRefresh();
    //     chargeHighVoltageReserviour();
    // }

    // encoderScanKey();
    // displayRefresh();
    // Serial.println(analogRead(A0));
}

void onEncoderLongKeyPress()
{
    counter = 99;
    //displayRefresh();
}

void onEncoderKeyPress()
{    
    RPGDConfiguation::DiceThrowConfiguation throwConfiguration = configuration->GetThrowConfiguration(currentThrowConfigurationIndex);
    
    dieDisplay->ShowResults(throwConfiguration.diceCount, currentDiceThrow->Throw());        
}

void onEncoderRotation(bool cwRotation)
{
    currentThrowConfigurationIndex += cwRotation ? 1 : -1;
    currentThrowConfigurationIndex = currentThrowConfigurationIndex % configuration->GetThrowConfigurationsCount();

    RPGDConfiguation::DiceThrowConfiguation throwConfiguration = configuration->GetThrowConfiguration(currentThrowConfigurationIndex);

    delete currentDiceThrow;
    currentDiceThrow = new DiceThrow(throwConfiguration.diceCount, throwConfiguration.dieFacesCount);
    dieDisplay->SetTitle(currentDiceThrow->GetTextualDescription());
}