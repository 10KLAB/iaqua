#include "HCSR04.h"

#define PERSON_SEN_TRIGG 30
#define PERSON_SEN_ECHO 31

namespace iAqua {
namespace objDetection {
HCSR04 personSensor(PERSON_SEN_TRIGG, PERSON_SEN_ECHO); // trigg, echo

bool detectPerson() {
  int distance = 0;
  const int read_cycles = 5;
  int average_distance = 0;
  const int detection_distance = 20;
  const int read_delay = 20;
  static unsigned long current_time = 0;
  const int new_read = 1000;

  if (millis() < current_time + new_read) {
    return false;
  }

  for (int i = 0; i < read_cycles; i++) {
    average_distance += personSensor.dist();
    delay(read_delay);
  }
  distance = average_distance / read_cycles;
  Serial.println("distance: " + String(distance));
  if (distance <= detection_distance) {
    current_time = millis();
    return true;
  } else {
    current_time = millis();
    return false;
  }
  current_time = millis();
  return false;
}

} // namespace objDetection
} // namespace iAqua