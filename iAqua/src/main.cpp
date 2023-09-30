#include <Arduino.h>
#include "digital_io.h"
#include "flow_metter.h"
#include "ligth_manager.h"
#include "object_detection.h"
#include "payment.h"
#include "screen_mananger.h"
#include "setup_machine.h"
#include "audio_manager.h"

#define LINE_1 20
#define LINE_2 45
#define SELECTION 45
#define CHANGE 46
#define BACK 47

void fillSequence();
bool personDetected();

void setup() {
  Serial.begin(9600);
  iAqua::digitalIO::setupIO();
  iAqua::payment::setupPayment();
  iAqua::flowMetter::setupFlowMetter();
  iAqua::screen::setupScreen();
  iAqua::screen::printScreen("       iAqua", LINE_1);
  iAqua::ligths::setupLigths();
  iAqua::audio::setupDFPlayer();
  delay(3000);
  iAqua::setup::initialiceSetup();
}

void loop() {
  iAqua::payment::relunchRFID();

  if (!personDetected()) {

    iAqua::ligths::rainbow();
    iAqua::screen::toggleText("       iAqua", " ", "  $500 pesos",
                              "      5 litros");
  }

  if (iAqua::payment::verifyCard() || iAqua::payment::readCoinsAmount()) {
    bool person_detected = personDetected();
    if (!person_detected) {
      iAqua::screen::printScreen("Bienvenido!", LINE_1);
      iAqua::ligths::meteorRain(10, 100, 30);
    }
    fillSequence();

    if (!person_detected) {
      iAqua::ligths::FadeOut(10, 100, 30);
      delay(1000);
    }
  }

}

bool verifyTimeout(bool reset) {
  static unsigned long current_time = 0;
  const unsigned long timeout = 10000;

  if (reset) {
    current_time = millis();
  }

  if (millis() < current_time + timeout) {
    return false;
  } else {
    // current_time = millis();
    return true;
  }
}

void fillSequence() {

  iAqua::digitalIO::turnOnFilters();
  iAqua::digitalIO::doorUp();
  verifyTimeout(true);
  while (!iAqua::digitalIO::readButton(SELECTION)) {
    iAqua::screen::toggleText("poner recipiente", "boca abajo", "presionar",
                              "seleccionar");
    if (verifyTimeout(false)) {
      iAqua::digitalIO::doorDown();
      return;
    }
  }
  iAqua::screen::printScreenTwoLines("Lavando", LINE_1, "reipiente", LINE_2);
  iAqua::digitalIO::doorDown();
  iAqua::flowMetter::washContainer();
  iAqua::digitalIO::doorUp();

  verifyTimeout(true);
  while (!iAqua::digitalIO::readButton(SELECTION)) {
    iAqua::screen::toggleText("poner recipiente", "boca arriba", "presionar",
                              "seleccionar");
    if (verifyTimeout(false)) {
      iAqua::digitalIO::doorDown();
      return;
    }
  }
  iAqua::screen::printScreenTwoLines("Llenando", LINE_1, "reipiente", LINE_2);
  iAqua::digitalIO::doorDown();
  iAqua::flowMetter::fillContainer();
  iAqua::digitalIO::turnOffFilters();
  iAqua::digitalIO::doorUp();

  verifyTimeout(true);
  while (!iAqua::digitalIO::readButton(SELECTION)) {
    iAqua::screen::toggleText("retirar", "recipiente", "presionar",
                              "seleccionar");
    if (verifyTimeout(false)) {
      iAqua::digitalIO::doorDown();
      return;
    }
  }
  iAqua::digitalIO::turnOnFilters();
  iAqua::flowMetter::washContainer();
  iAqua::digitalIO::turnOffFilters();
  iAqua::digitalIO::doorDown();
}

bool personDetected() {
  static bool new_detection = true;
  static bool reset = false;
  static unsigned long current_time = 0;
  const int new_detection_delay = 5000;

  if (new_detection) {
    if (iAqua::objDetection::detectPerson()) {
      iAqua::screen::printScreen("Bienvenido!", LINE_1);
      iAqua::ligths::meteorRain(10, 100, 30);
      new_detection = false;
      reset = true;
      current_time = millis();
      return true;
    }
  }
  if (!new_detection && reset) {
    if (millis() > current_time + new_detection_delay) {
      new_detection = true;
      iAqua::ligths::FadeOut(10, 100, 30);
      current_time = millis();
      reset = false;
    }
    return true;
  } else {
    return false;
  }
}