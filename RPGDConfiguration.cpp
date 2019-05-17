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

#include "RPGDConfiguration.h"

RPGDConfiguation::RPGDConfiguation()
{
}

uint8_t RPGDConfiguation::GetThrowConfigurationsCount()
{
  for (int configurationIndex = 0; configurationIndex < EEPROM_THROW_CONFIG_MAX_ENTRIES; configurationIndex++)
  {
    if (this->GetThrowConfiguration(configurationIndex).diceCount == 0)
    {
      return configurationIndex;
    }
  }

  return EEPROM_THROW_CONFIG_MAX_ENTRIES - 1;
}

RPGDConfiguation::DiceThrowConfiguation RPGDConfiguation::GetThrowConfiguration(uint8_t configurationIndex)
{
  return {
      EEPROM.read(EEPROM_THROW_CONFIG_BASE_ADDRESS + (configurationIndex * EEPROM_THROW_CONFIG_ENTRY_SIZE)),
      EEPROM.read(EEPROM_THROW_CONFIG_BASE_ADDRESS + (configurationIndex * EEPROM_THROW_CONFIG_ENTRY_SIZE) + 1)};  
}
