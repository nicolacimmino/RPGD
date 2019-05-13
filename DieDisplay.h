
#include <SSD1306AsciiAvrI2c.h>

class DieDisplay
{
public:
  DieDisplay(SSD1306AsciiAvrI2c *oled);
  void SetTitle(char *title);
  void ShowResults(uint8_t throwsCount, uint8_t *throws);

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
};
