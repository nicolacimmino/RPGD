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

#include <SSD1306AsciiAvrI2c.h>

class DieDisplay
{
public:
  DieDisplay(SSD1306AsciiAvrI2c *oled);
  void SetTitle(char *title);
  void ClearResults(uint8_t throwsCount);
  void ShowResults(uint8_t throwsCount, uint8_t *throws);
  void ShowEntropyWaitScreen();
  void ShowProgress();
  
private:
  SSD1306AsciiAvrI2c *oled;

  uint8_t positions[5][2] = {
      {2, 10},
      {2, 90},
      {4, 50},
      {6, 10},
      {6, 90}};

  uint8_t *resultsLayouts[5][5] = {
      {positions[2]},
      {positions[0], positions[4]},
      {positions[0], positions[2], positions[4]},
      {positions[0], positions[1], positions[3], positions[4]},
      {positions[0], positions[1], positions[2], positions[3], positions[4]}};

  void printCentered(const char *text);
};
