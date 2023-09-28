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

byte* readCardUID(){
const int uuid_size = 4;
byte* uuid = new byte[uuid_size];
byte address[uuid_size] = {CARD_ADRSS_1, CARD_ADRSS_2, CARD_ADRSS_3, CARD_ADRSS_4};

for(int i=0; i<4; i){
  EEPROM.get(address[i], uuid[i]);
}
return uuid;
}

// int* createArray(int size) {
//   int* arr = new int[size]; // Create a dynamic integer array on the heap
//   for (int i = 0; i < size; i++) {
//     arr[i] = i * 2; // Fill the array with some data
//   }
//   return arr; // Return a pointer to the array
// }


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

void writteUUID(byte a, byte b, byte c, byte d){
  const int uuid_size = 4;
  byte* read_uuid = readCardUID();
  byte uuid[uuid_size] = {0};

  for (int i = 0; i < uuid_size; i++) {
    uuid[i] = read_uuid[i];
  }
  // Don't forget to free the memory allocated for the array
  delete[] read_uuid;

  byte incoming_uuid[uuid_size] ={a, b, c, d};
  byte address[uuid_size] = {CARD_ADRSS_1, CARD_ADRSS_2, CARD_ADRSS_3, CARD_ADRSS_4};

  for(int i = 0; i < uuid_size; i++){
    if(uuid[i] != incoming_uuid[i]){
      EEPROM.put(address[i], incoming_uuid[i]);
    }
  }

}
} // namespace eeprom
} // namespace iAqua


