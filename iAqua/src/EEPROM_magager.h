#include <Arduino.h>
#ifndef EEPROM_MANAGER_H_
#define EEPROM_MANAGER_H_

namespace iAqua {
namespace eeprom {
float readLitterAmount();
float readKoCompensation();
void writteLittersAmount(float liters);
void writteKoCompensation(float ko);
int readPrice();
int readTimeoutFill();
void writteFillTimeout(int timeout);
void writtePrice(int price);

} // namespace eeprom
} // namespace iAqua

#endif