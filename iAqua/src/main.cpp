#include <Arduino.h>
#include "screen_mananger.h"

void setup() {
  
  iAqua::screen::setupScreen();
  iAqua::screen::printScreen("Hello", 30);

}

void loop() {
  delay(1000);

}
