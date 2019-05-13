
#include "DieDisplay.h"

DieDisplay::DieDisplay(SSD1306AsciiAvrI2c *oled)
{
    this->oled = oled;

   
}

void DieDisplay::SetTitle(char *title)
{
    oled->setCursor(0, 0);
    oled->setFont(System5x7);
    oled->set1X();
    oled->print(title);
    oled->clearToEOL();
}

void DieDisplay::ShowResults(uint8_t throwsCount, uint8_t *throws)
{
    oled->setFont(lcdnums12x16);
    oled->set1X();

    for (uint8_t ix = 1; ix < 7; ix++)
    {
        oled->setCursor(0, ix);
        oled->clearToEOL();
    }

    for (uint8_t ix = 0; ix < throwsCount; ix++)
    {
        oled->setCursor(this->resultsLayouts[throwsCount - 1][ix][1], this->resultsLayouts[throwsCount - 1][ix][0]);
        oled->print(throws[ix]);
    }
}
