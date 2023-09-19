#include "digital_io.h"
#include "screen_mananger.h"
#include "EEPROM_magager.h"

#define SELECTION 45
#define CHANGE 46
#define BACK 47

namespace iAqua {
namespace setup {

void selectLitters() {
  int liters = 1;

  while (!iAqua::digitalIO::readButton(SELECTION)) {
    static unsigned long current_time = millis();
    const int refresh_time = 300;
    if (millis() >= current_time + refresh_time) {
      iAqua::screen::printScreenTwoLines("Select Lts", 25,
                                         "L= " + String(liters), 42);
      current_time = millis();
    }

    const int max_liters = 10;
    if (iAqua::digitalIO::readButton(CHANGE)) {
      liters++;
      if (liters >= max_liters) {
        liters = max_liters;
      }
      iAqua::digitalIO::waitLeftButton(CHANGE);
    }

    const int min_liters = 1;
    if (iAqua::digitalIO::readButton(BACK)) {
      liters--;
      if (liters <= min_liters) {
        liters = min_liters;
      }
      iAqua::digitalIO::waitLeftButton(BACK);
    }
  }

  iAqua::screen::printScreen("exiting", 25);
}

void initialiceSetup() {
  const int delay_message = 1000;
  if (iAqua::digitalIO::readButton(BACK) &&
      iAqua::digitalIO::readButton(CHANGE)) {
    iAqua::screen::printScreen("Config menu", 30);
    delay(delay_message);
    selectLitters();
  }
}

} // namespace setup
} // namespace iAqua