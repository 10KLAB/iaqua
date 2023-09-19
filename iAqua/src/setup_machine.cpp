#include "EEPROM_magager.h"
#include "digital_io.h"
#include "flow_metter.h"
#include "screen_mananger.h"

#define SELECTION 45
#define CHANGE 46
#define BACK 47

#define LINE_1 20
#define LINE_2 45

namespace iAqua {
namespace setup {

void selectLitters() {
  int liters = 1;

  iAqua::screen::printScreenTwoLines("Select LTS?", LINE_1, "Yes / No", LINE_2);
  if (iAqua::digitalIO::selectYesOrNo()) {

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
  }
  iAqua::eeprom::writteLittersAmount(liters);
  iAqua::screen::printScreen("Exiting...", 25);
  //   Serial.println("liters = " + String(iAqua::eeprom::readLitterAmount()));
}

float calculateKo(float liters) {
  int teorical_liters = iAqua::eeprom::readLitterAmount();
  float ko = teorical_liters / liters;
  Serial.println("ko = " + String(ko));
  return ko;
}

void calibrateDispensation() {
  const int delay_message = 1500;
  iAqua::screen::printScreenTwoLines("Calibrate lts?", LINE_1, "Yes / No",
                                     LINE_2);
  int liters = iAqua::eeprom::readLitterAmount();
  if (iAqua::digitalIO::selectYesOrNo()) {
    delay(delay_message);
    iAqua::screen::printScreenTwoLines("Current lts", LINE_1, String(liters),
                                       LINE_2);
    delay(delay_message);
    iAqua::digitalIO::doorUp();

    while (!iAqua::digitalIO::readButton(SELECTION)) {
      iAqua::screen::toggleText("Put", "recipient", "and press", "select");
    }

    iAqua::screen::printScreen("Filling...", LINE_1);
    iAqua::digitalIO::doorDown();
    iAqua::flowMetter::fillContainer();

    float real_liters = liters;
    while (!iAqua::digitalIO::readButton(SELECTION)) {
      iAqua::screen::printScreen("Real lts: " + String(real_liters), LINE_1);

      if (iAqua::digitalIO::readButton(CHANGE)) {
        real_liters += 0.2;
      }
      if (iAqua::digitalIO::readButton(BACK)) {
        real_liters -= 0.2;
        if (real_liters <= 0) {
          real_liters = 0;
        }
      }
    }

    iAqua::screen::printScreen("Calculating...", LINE_1);
    iAqua::eeprom::writteKoCompensation(calculateKo(real_liters));

    iAqua::digitalIO::doorUp();
    while (!iAqua::digitalIO::readButton(SELECTION)) {
      iAqua::screen::toggleText("Remove", "recipient", "and press", "select");
    }
    iAqua::digitalIO::doorDown();
    delay(delay_message);
    iAqua::screen::printScreen("Exiting...", LINE_1);
  }
}

void selectFillTimeout() {
  const int sec_to_millis = 1000;
  iAqua::screen::printScreenTwoLines("Fill timeout?", LINE_1, "Yes / No",
                                     LINE_2);
  int timeout = iAqua::eeprom::readTimeoutFill();
  int seconds = timeout / sec_to_millis;
  if (iAqua::digitalIO::selectYesOrNo()) {
    while (!iAqua::digitalIO::readButton(SELECTION)) {
      if (iAqua::digitalIO::readButton(CHANGE)) {
        seconds += 1;
        iAqua::digitalIO::waitLeftButton(CHANGE);
      }
      if (iAqua::digitalIO::readButton(BACK)) {
        seconds -= 1;
        if (seconds <= 1) {
          seconds = 1;
        }
        iAqua::digitalIO::waitLeftButton(BACK);
      }

      static unsigned long current_time = millis();
      const int refresh_time = 300;
      if (millis() >= current_time + refresh_time) {
        iAqua::screen::printScreenTwoLines("Seconds", LINE_1, String(seconds),
                                           LINE_2);
        current_time = millis();
      }
    }
    timeout = seconds * sec_to_millis;
    iAqua::eeprom::writteFillTimeout(timeout);
    iAqua::screen::printScreen("Exiting...", LINE_2);
  }
}

void selectPrice() {
  const int int_to_pesos = 100;
  iAqua::screen::printScreenTwoLines("Select price?", LINE_1, "Yes / No",
                                     LINE_2);
  int price = iAqua::eeprom::readPrice();
  int pesos = price * int_to_pesos;
  if (iAqua::digitalIO::selectYesOrNo()) {
    while (!iAqua::digitalIO::readButton(SELECTION)) {
      if (iAqua::digitalIO::readButton(CHANGE)) {
        pesos += int_to_pesos;
        iAqua::digitalIO::waitLeftButton(CHANGE);
      }
      if (iAqua::digitalIO::readButton(BACK)) {
        pesos -= int_to_pesos;
        if (pesos <= int_to_pesos) {
          pesos = int_to_pesos;
        }
        iAqua::digitalIO::waitLeftButton(BACK);
      }

      static unsigned long current_time = millis();
      const int refresh_time = 300;
      if (millis() >= current_time + refresh_time) {
        iAqua::screen::printScreenTwoLines("Seconds", LINE_1, String(pesos),
                                           LINE_2);
        current_time = millis();
      }
    }
    price = pesos / int_to_pesos;
    iAqua::eeprom::writtePrice(price);
    iAqua::screen::printScreen("Exiting...", LINE_2);
  }
}

void initialiceSetup() {
  const int delay_message = 1000;
  if (iAqua::digitalIO::readButton(BACK) &&
      iAqua::digitalIO::readButton(CHANGE)) {
    iAqua::screen::printScreen("Config menu", 30);
    // delay(delay_message);
    // selectLitters();
    // delay(delay_message);
    // calibrateDispensation();
    // selectFillTimeout();
    selectPrice();
  }
}

} // namespace setup
} // namespace iAqua