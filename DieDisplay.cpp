//
// DieDisplay wraps the logic to manage the display real estate and provides
// methods to display the title, a throw result etc. in a consistent layout.
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

#include "DieDisplay.h"

DieDisplay::DieDisplay(SSD1306AsciiAvrI2c *oled)
{
    this->oled = oled;
}

void DieDisplay::SetTitle(char *title)
{
    oled->setFont(System5x7);
    oled->set1X();
    
    oled->clear(0, oled->displayWidth(), 0, 0);
    uint8_t xOffset = (oled->displayWidth() - (strlen(title) * 6 - 1)) / 2;

    oled->setCursor(xOffset, 0);    
    oled->print(title);    
}

void DieDisplay::ClearResults(uint8_t throwsCount)
{
    oled->setFont(lcdnums12x16);
    oled->set1X();
    oled->clear(0, oled->displayWidth(), 1, oled->displayRows());

    for (uint8_t ix = 0; ix < throwsCount; ix++)
    {
        oled->setCursor(this->resultsLayouts[throwsCount - 1][ix][1], this->resultsLayouts[throwsCount - 1][ix][0]);
        oled->print("-");
    }
}

void DieDisplay::ShowResults(uint8_t throwsCount, uint8_t *throws)
{
    this->ClearResults(throwsCount);

    for (uint8_t ix = 0; ix < throwsCount; ix++)
    {
        oled->setCursor(this->resultsLayouts[throwsCount - 1][ix][1], this->resultsLayouts[throwsCount - 1][ix][0]);
        oled->print(throws[ix]);
    }
}
