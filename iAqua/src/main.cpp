#include <Arduino.h>
#include "screen_mananger.h"
#include "digital_io.h"
#include "flow_metter.h"
#include "setup_machine.h"
#include "ligth_manager.h"
#include "object_detection.h"

#define LINE_1 20
#define LINE_2 45
#define SELECTION 45
#define CHANGE 46
#define BACK 47

void fillSequence();

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
  
  // iAqua::flowMetter::fillContainer();
  // iAqua::setup::initialiceSetup();
  iAqua::ligths::rainbow();
  iAqua::screen::toggleText("       iAqua", " ", "  $500 pesos", "      5 litros");

  if(iAqua::objDetection::detectPerson()){
    iAqua::screen::printScreen("Bienvenido!", LINE_1);
    iAqua::ligths::meteorRain(10, 100, 30);
    delay(1000);
    iAqua::ligths::FadeOut(10, 100, 30);
    fillSequence();
  }

}

void fillSequence(){
  iAqua::digitalIO::doorUp();
  while(!iAqua::digitalIO::readButton(SELECTION)){
    iAqua::screen::toggleText("poner recipiente", "boca abajo", "presionar", "seleccionar");
  }
  iAqua::screen::printScreenTwoLines("Lavando", LINE_1, "reipiente", LINE_2);
  iAqua::digitalIO::doorDown();
  iAqua::flowMetter::washContainer();
  iAqua::digitalIO::doorUp();

  while(!iAqua::digitalIO::readButton(SELECTION)){
    iAqua::screen::toggleText("poner recipiente", "boca arriba", "presionar", "seleccionar");
  }
  iAqua::screen::printScreenTwoLines("Llenando", LINE_1, "reipiente", LINE_2);
  iAqua::digitalIO::doorDown();
  iAqua::flowMetter::fillContainer();
  iAqua::digitalIO::doorUp();

  while(!iAqua::digitalIO::readButton(SELECTION)){
    iAqua::screen::toggleText("retirar", "recipiente", "presionar", "seleccionar");
  }
  iAqua::digitalIO::doorDown();
}
