// ChargePump implements ancillary functions for the TRNG charge pump.
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

#define PIN_NOISE_IN A0
#define PIN_CHG_PUMP_SENSE A1

#define PIN_CHG_PUMP0 2
#define PIN_CHG_PUMP1 3
#define PIN_CHG_PUMP2 4
#define PIN_CHG_PUMP3 5
#define CHG_PUMP_LIMIT_HI 1000
#define CHG_PUMP_LIMIT_LO 700
#define CHG_PUMP_ALARM_DELAY_MS 10000

volatile long chgPumpLevel;
volatile bool highVoltageReserviourGood = false;

void initChargePump()
{
    //  Set ADC prescaler to 16 so we get higher sample rate than with default settings.
    _SFR_BYTE(ADCSRA) |= _BV(ADPS2);  // Set ADPS2
    _SFR_BYTE(ADCSRA) &= ~_BV(ADPS1); // Clear ADPS1
    _SFR_BYTE(ADCSRA) &= ~_BV(ADPS0); // Clear ADPS0

    pinMode(PIN_NOISE_IN, INPUT);
    pinMode(PIN_CHG_PUMP_SENSE, INPUT);

    // Use internal 1.1V reference for the A/D converters
    // since the noise levels we get are rather low.
    analogReference(INTERNAL); 
}

/**
 * Run the charge pump until it reaches the preset high level. This function blocks
 * until the level is reached. Upon return the charge pump is stopped and the reserviour
 * cap loaded.
 */
void chargeHighVoltageReserviour()
{
    setChargePumpOutputsHiZ(false);        
    highVoltageReserviourGood = false;
    
    unsigned char phase = 0;
    unsigned long startTime = millis();
    while ((chgPumpLevel = analogRead(PIN_CHG_PUMP_SENSE)) < CHG_PUMP_LIMIT_HI)
    {
        digitalWrite(PIN_CHG_PUMP0, (phase % 2 == 0) ? HIGH : LOW);
        digitalWrite(PIN_CHG_PUMP1, (phase % 2 == 0) ? LOW : HIGH);
        digitalWrite(PIN_CHG_PUMP2, (phase % 2 == 0) ? HIGH : LOW);
        digitalWrite(PIN_CHG_PUMP2, (phase % 2 == 0) ? LOW : HIGH);
        phase++;
            
        // millis wrapped around, don't get stuck in alarm.
        if (millis() < startTime)
        {
            startTime = millis();
        }

        if (millis() - startTime > CHG_PUMP_ALARM_DELAY_MS)
        {
        //    chargePumpAlarmAndHalt(chgPumpLevel);
        }
    }

    delay(20);
    setChargePumpOutputsHiZ(true);    
    highVoltageReserviourGood = true;
}

bool isHighVoltageReseviourAboveMin()
{
    highVoltageReserviourGood = (chgPumpLevel = analogRead(PIN_CHG_PUMP_SENSE)) > CHG_PUMP_LIMIT_LO;
    return highVoltageReserviourGood;
}

/**
 * Set the charge pump output hi impedance.
 */
void setChargePumpOutputsHiZ(bool on)
{
    pinMode(PIN_CHG_PUMP0, on ? INPUT : OUTPUT);
    pinMode(PIN_CHG_PUMP1, on ? INPUT : OUTPUT);
    pinMode(PIN_CHG_PUMP2, on ? INPUT : OUTPUT);
    pinMode(PIN_CHG_PUMP3, on ? INPUT : OUTPUT);   
}
