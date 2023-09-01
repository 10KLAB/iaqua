#include <Arduino.h>
#include "test.h"

void setup() {
  iAqua::startTest::setupScreen();
  iAqua::startTest::setupButtons();
}

void loop() {
  iAqua::startTest::helloWorld();
  iAqua::startTest::buttons();
}
