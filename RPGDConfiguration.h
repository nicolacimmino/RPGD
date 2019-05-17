//
// RPGDConfiguation wraps the logic to access various configuration parameters
// stored in EEPROM. 
//
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

#include <EEPROM.h>

#define EEPROM_THROW_CONFIG_BASE_ADDRESS 0
#define EEPROM_THROW_CONFIG_MAX_ENTRIES 4
#define EEPROM_THROW_CONFIG_ENTRY_SIZE 2

class RPGDConfiguation
{
public:
  struct DiceThrowConfiguation
  {
    uint8_t diceCount;
    uint8_t dieFacesCount;
  };

  RPGDConfiguation();
  uint8_t GetThrowConfigurationsCount();
  DiceThrowConfiguation GetThrowConfiguration(uint8_t configurationIndex);

private:
  uint8_t throwsCount;
};
