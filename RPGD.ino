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
#include <RotaryEncoder.h> // https://github.com/nicolacimmino/RotaryEncoder
#include <TRNG.h>          // https://github.com/nicolacimmino/TRNG

uint8_t counter;

DieDisplay *dieDisplay;
SSD1306AsciiAvrI2c *oled;
RPGDConfiguation *configuration;
uint8_t currentThrowConfigurationIndex;
DiceThrow *currentDiceThrow;
RotaryEncoder rotaryEncoder;
TRNG trng;

void writeConfigurationToEEPROM()
{
    EEPROM.write(0, 4);
    EEPROM.write(1, 6);
    EEPROM.write(2, 5);
    EEPROM.write(3, 10);
    EEPROM.write(4, 2);
    EEPROM.write(5, 100);
    EEPROM.write(6, 1);
    EEPROM.write(7, 6);
    EEPROM.write(8, 0);
    EEPROM.write(9, 0);
}

void setup()
{
    //writeConfigurationToEEPROM();

    Serial.begin(115200);

    oled = new SSD1306AsciiAvrI2c();
    oled->begin(&Adafruit128x64, DISPLAY_I2C_ADDRESS);

    dieDisplay = new DieDisplay(oled);

    trng.begin(PIN_CHG_PUMP0, PIN_CHG_PUMP1, PIN_CHG_PUMP2, PIN_CHG_PUMP3, PIN_CHG_PUMP_SENSE, PIN_CHG_PUMP_NOISEIN);

    dieDisplay->ShowEntropyWaitScreen();
    while (!trng.isRandomDataReady())
    {
        trng.loop();
        dieDisplay->ShowProgress();
    }

    configuration = new RPGDConfiguation();
    currentThrowConfigurationIndex = 0;
    applyCurrentThrowConfiguration();

    rotaryEncoder.begin(PIN_ENC_A, PIN_ENC_B, PIN_ENC_SW);
    rotaryEncoder.registerOnClickCallback(onEncoderKeyPress);
    rotaryEncoder.registerOnLongPressCallback(onEncoderLongKeyPress);
    rotaryEncoder.registerOnRotationCallback(onEncoderRotation);
}

void loop()
{
    rotaryEncoder.loop();
    trng.loop();
}

void onEncoderLongKeyPress()
{
    applyCurrentThrowConfiguration();
}

void onEncoderKeyPress()
{
    dieDisplay->ShowResults(currentDiceThrow->GetDiceCount(), currentDiceThrow->Throw());
}

void onEncoderRotation(bool cwRotation, int position)
{    
    if ((currentThrowConfigurationIndex == 0 && !cwRotation) || (currentThrowConfigurationIndex == configuration->GetThrowConfigurationsCount() - 1 && cwRotation))
    {        
        return;
    }

    currentThrowConfigurationIndex += cwRotation ? 1 : -1;
    applyCurrentThrowConfiguration();
}

void applyCurrentThrowConfiguration()
{
    RPGDConfiguation::DiceThrowConfiguation throwConfiguration = configuration->GetThrowConfiguration(currentThrowConfigurationIndex);

    delete currentDiceThrow;
    currentDiceThrow = new DiceThrow(throwConfiguration.diceCount, throwConfiguration.dieFacesCount, &trng);
    dieDisplay->SetTitle(currentDiceThrow->GetTextualDescription());
    dieDisplay->ClearResults(currentDiceThrow->GetDiceCount());
}