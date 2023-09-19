#include <Arduino.h>
#include "screen_mananger.h"
#include "digital_io.h"
#include "flow_metter.h"
#include "setup_machine.h"

void setup() {
  Serial.begin(9600);
  iAqua::digitalIO::setupIO();
  iAqua::flowMetter::setupFlowMetter();
  iAqua::screen::setupScreen();
  iAqua::screen::printScreen("Hello", 30);

}

void loop() {
  // iAqua::buttons::testButtons();
  // iAqua::digitalIO::testValves();
  // iAqua::digitalIO::testRelays();
  // iAqua::digitalIO::testDoor();
  // iAqua::flowMetter::testFlowMetter();
  iAqua::setup::initialiceSetup();



}
