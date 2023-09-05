#include <Arduino.h>
#include "screen_mananger.h"
#include "digital_io.h"

void setup() {
  iAqua::digitalIO::setupIO();
  iAqua::screen::setupScreen();
  iAqua::screen::printScreen("Hello", 30);

}

void loop() {
  // iAqua::buttons::testButtons();
  iAqua::digitalIO::testValves();
  iAqua::digitalIO::testRelays();
  delay(10);

}
