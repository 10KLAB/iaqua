#include "EEPROM_magager.h"
#include <EEPROM.h>


#define LITERS_ADRSS 0
#define K_ADRSS 5
#define TIMEOUT_FILL_ADRSS 6
#define PRICE_ADRSS 7

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

int readTimeoutFill(){
  int timeout = 0;
  EEPROM.get(TIMEOUT_FILL_ADRSS, timeout);
  return timeout;
}

int readPrice(){
  int price = 0;
  EEPROM.get(PRICE_ADRSS, price);
  return price;
}

void writteFillTimeout(int timeout) {
  if (readTimeoutFill() != timeout) {
    EEPROM.put(TIMEOUT_FILL_ADRSS, timeout);
  }
}

void writtePrice(int price) {
  if (readPrice() != price) {
    EEPROM.put(PRICE_ADRSS, price);
  }
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