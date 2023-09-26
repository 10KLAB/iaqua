#include "EEPROM_magager.h"
#include <EEPROM.h>


#define LITERS_ADRSS 0
#define K_ADRSS 4
#define TIMEOUT_FILL_ADRSS 8
#define PRICE_ADRSS 10
#define CARD_ADRSS_1 11
#define CARD_ADRSS_2 12
#define CARD_ADRSS_3 13
#define CARD_ADRSS_4 14

namespace iAqua {
namespace eeprom {
String readCardUID(){
byte uuid[4]={0, 0, 0, 0};
int address[4] = {CARD_ADRSS_1, CARD_ADRSS_2, CARD_ADRSS_3, CARD_ADRSS_4};

for(int i=0; i<4; i){
  EEPROM.get(address[i], uuid[i]);
}
String string_address = String((char*)address);

// byte byteArray[5];
//   strcpy((char *)byteArray,"0123");
//   String myString = String((char *)byteArray);

//   String myString = String((char*)myByteArray);

}

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
  if (readLitterAmount() != liters) {
    EEPROM.put(LITERS_ADRSS, liters);
  }
}

void writteKoCompensation(float ko) {
  if (readKoCompensation() != ko) {
    EEPROM.put(K_ADRSS, ko);
  }
}
} // namespace eeprom
} // namespace iAqua


