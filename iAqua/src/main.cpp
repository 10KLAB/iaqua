#include <Arduino.h>
#include "test.h"

void setup() {
  iAqua::startTest::set();
}

void loop() {
  iAqua::startTest::helloWorld();
}
