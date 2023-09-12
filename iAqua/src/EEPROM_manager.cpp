#include "EEPROM_magager.h"
#include <EEPROM.h>


#define LITERS_ADRSS 0
#define K_ADRSS 5

namespace iAqua {
namespace eeprom {

float readLitterAmount() {
  float saved_litters = 0;
  EEPROM.get(LITERS_ADRSS, saved_litters);
  return saved_litters;
}
float readKoCompensation() {
  float ko = 0;
  EEPROM.get(K_ADRSS, ko);
  return ko;
}

void writteLittersAmount(float liters) {
  float saved_liters = 0;
  if (readLitterAmount() != liters) {
    EEPROM.put(LITERS_ADRSS, liters);
  }
}

void writteKoCompensation(float ko) {
  float saved_ko = 0;
  if (readKoCompensation() != ko) {
    EEPROM.put(K_ADRSS, ko);
  }
}
} // namespace eeprom
} // namespace iAqua