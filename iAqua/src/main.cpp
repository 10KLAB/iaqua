#include <Arduino.h>
#include "screen_mananger.h"
#include "digital_io.h"
#include "flow_metter.h"
#include "setup_machine.h"
#include "ligth_manager.h"

#define LINE_1 20
#define LINE_2 45

void setup() {
  Serial.begin(9600);
  iAqua::digitalIO::setupIO();
  iAqua::flowMetter::setupFlowMetter();
  iAqua::screen::setupScreen();
  iAqua::screen::printScreen("       iAqua", 30);
  iAqua::ligths::setupLigths();
  delay(3000);
  iAqua::setup::initialiceSetup();
}

void loop() {
  // iAqua::buttons::testButtons();
  // iAqua::digitalIO::testValves();
  // iAqua::digitalIO::testRelays();
  // iAqua::digitalIO::testDoor();
  // iAqua::flowMetter::testFlowMetter();
  
  iAqua::ligths::rainbow();

}
