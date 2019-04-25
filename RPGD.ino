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


#define PIN_ENC_A 10
#define PIN_ENC_B 11
#define PIN_ENC_SW 12

uint8_t counter;

void setup()
{
    pinMode(PIN_ENC_A, INPUT_PULLUP);
    pinMode(PIN_ENC_B, INPUT_PULLUP);
    pinMode(PIN_ENC_SW, INPUT_PULLUP);
    
    displaySetup();
    setupRotaryEncoder();

    initChargePump();
    Serial.begin(115200);
}

void loop()
{
    if(!isHighVoltageReseviourAboveMin()) {
        displayRefresh();
        chargeHighVoltageReserviour();
    }

    encoderScanKey();
    displayRefresh();
    Serial.println(analogRead(A0));
}

void onEncoderLongKeyPress() {
    counter = 99;
    displayRefresh();
}

void onEncoderKeyPress() {
    counter = random(1, 10);   
    displayRefresh();
}

void onEncoderRotation(bool cwRotation) {
    counter += cwRotation ? 1 : -1;
}