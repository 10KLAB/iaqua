#include "flow_metter.h"
#include "EEPROM_magager.h"
#include "FlowMeter.h"
#include "digital_io.h"
#include "screen_mananger.h"


#define FLOWMETTER_1 20
#define FILL_VALVE 4
#define WASH_VALVE 5
#define PRESSURE_SENSOR A13

#define LINE_1 20
#define LINE_2 45
#define CHANGE 46
#define BACK 47


namespace iAqua {
namespace flowMetter {
FlowMeter *Meter1;
void Meter1ISR() { Meter1->count(); }
void setupFlowMetter() {
  Meter1 = new FlowMeter(digitalPinToInterrupt(FLOWMETTER_1),
                         UncalibratedSensor, Meter1ISR, RISING);
  pinMode(PRESSURE_SENSOR, INPUT);
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

bool verifyFillingTimeout(unsigned long timeout, bool reset) {
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
  const int sec_to_millis = 1000;
  unsigned long int timeout = iAqua::eeprom::readTimeoutFill();
  timeout = timeout * sec_to_millis;

  Serial.println("liters: " + String(liters) + " ko: " + String(ko) + " timeout: " + String(timeout));
  iAqua::digitalIO::setValve(FILL_VALVE, HIGH);

  delay(3000);
  
  Meter1->setTotalVolume(0.00);
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

float readPressure(){
  float pressure = 0;
  float voltage = 0;
  float pressure_average = 0;
  const int read_cycles = 10;
  const int delay_read = 50;
  const float PSI_factor = 0.145038;
  const float pressure_offset = 0.40;

  for(int i = 0; i < read_cycles; i++){
    voltage = analogRead(PRESSURE_SENSOR) * 5.00/1024;
    pressure = (voltage - pressure_offset) * 250; //to Kpa
    pressure_average += pressure;
    delay(delay_read);
  }
  pressure = pressure_average / read_cycles;
  pressure = pressure * PSI_factor;
  
  return pressure;
}

void showPressure(){
  static unsigned long current_time = 0;
  const int show_time = 5000;
  if(iAqua::digitalIO::readButton(CHANGE) && iAqua::digitalIO::readButton(BACK)){
    current_time = millis();
    while(millis() < current_time + show_time){
      float pressure = readPressure();
      iAqua::screen::printScreenTwoLines("Pressure", LINE_1, String(pressure) + " PSI", LINE_2);
    }
  }
}


} // namespace flowMetter
} // namespace iAqua