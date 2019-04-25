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

#include <PinChangeInterrupt.h>

extern void onEncoderRotation(bool cwRotation);

extern void onEncoderKeyPress();

extern void onEncoderLongKeyPress();

void  setupRotaryEncoder()
{
    attachPCINT(digitalPinToPCINT(PIN_ENC_A), onEncoderAChange, CHANGE);    
}

void onEncoderAChange()
{
    uint8_t trigger = getPinChangeInterruptTrigger(digitalPinToPCINT(PIN_ENC_A));
    bool cwRotation = (trigger == RISING) ? !digitalRead(PIN_ENC_B) : digitalRead(PIN_ENC_B);
    onEncoderRotation(cwRotation);
}

/**
 * Change mode. 
 * 
 * Change mode is entered when pressing the encoder switch. A short press will change the encode mode while
 * a long one will change the encoder dynamic mode.
 * 
 */
void encoderScanKey()
{
    if(digitalRead(PIN_ENC_SW) != 0) {
        return;
    }

    // Allow the switch to stabilise.
    byte debounce = 0x55;
    while (debounce != 0x00)
    {
        debounce = (debounce < 1) | (digitalRead(PIN_ENC_SW) & 1);
        delay(1);
    }

    // Wait for the switch to be released or a timeout of 500mS to expire.
    unsigned long initialTime = millis();
    while ((millis() - initialTime < 500) && digitalRead(PIN_ENC_SW) == 0)
    {
        delay(1);
    }

    if (digitalRead(PIN_ENC_SW) == 0)
    {        
        onEncoderLongKeyPress();
    }
    else
    {
        onEncoderKeyPress();
    }

    while(digitalRead(PIN_ENC_SW) == 0) {        
        delay(1);
    }    
}