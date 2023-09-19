#include "flow_metter.h"
#include "EEPROM_magager.h"
#include "FlowMeter.h"
#include "digital_io.h"
#include "screen_mananger.h"


#define FLOWMETTER_1 20
#define FILL_VALVE 4
#define WASH_VALVE 5

namespace iAqua {
namespace flowMetter {
FlowMeter *Meter1;
void Meter1ISR() { Meter1->count(); }
void setupFlowMetter() {
  Meter1 = new FlowMeter(digitalPinToInterrupt(FLOWMETTER_1),
                         UncalibratedSensor, Meter1ISR, RISING);
}

void testFlowMetter() {
  Meter1->setTotalVolume(0.00);
  const int period = 100;
  static unsigned long currentTime = 0;
  const int refresh_screen_time = 1000;

  while (Meter1->getTotalVolume() < 5) {
    Meter1->tick(period);
    Serial.println(Meter1->getTotalVolume());

    if (millis() >= currentTime + refresh_screen_time) {
      iAqua::screen::printScreen("L= " + String(Meter1->getTotalVolume()), 35);
      currentTime = millis();
    }
  }
}

bool verifyFillingTimeout(int timeout, bool reset) {
  static unsigned long current_time = 0;

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

void fillContainer() {
  float ko = iAqua::eeprom::readKoCompensation();
  float liters = iAqua::eeprom::readLitterAmount();
  const int refresh_period = 100;
  const int timeout = 2000;

  Meter1->setTotalVolume(0.00);
  Serial.println("liters: " + String(liters) + " ko: " + String(ko));
  iAqua::digitalIO::setValve(FILL_VALVE, HIGH);
  verifyFillingTimeout(timeout, true);
  while ((Meter1->getTotalVolume() < liters * ko) &&
         (!verifyFillingTimeout(timeout, false))) {
    Meter1->tick(refresh_period);
    Serial.println(Meter1->getTotalVolume());
  }
  iAqua::digitalIO::setValve(FILL_VALVE, LOW);
}

void washContainer(){
    const int wash_time = 2000;

    iAqua::digitalIO::setValve(WASH_VALVE, HIGH);
    delay(wash_time);
    iAqua::digitalIO::setValve(WASH_VALVE, LOW);
}

} // namespace flowMetter
} // namespace iAqua