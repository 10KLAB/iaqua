#include <Wire.h>
#include <SPI.h>
#include "MFRC522.h"
#include "payment.h"
#include "screen_mananger.h"
#include "EEPROM_magager.h"


#define COIN_COUNTER 2

#define RST_PIN 49 // Reset
#define SS_PIN 48  // SDA
// SCK=52/MOSI=51/MISO=50

#define LINE_1 20
#define LINE_2 45
const int delay_message = 1000;

namespace iAqua {
namespace payment {

MFRC522 cardReader(SS_PIN, RST_PIN);

int coins_count = 0;

void coinsCounter() { coins_count++; }

void setupPayment() {
  pinMode(COIN_COUNTER, INPUT);
  attachInterrupt(digitalPinToInterrupt(COIN_COUNTER), coinsCounter, RISING);
   SPI.begin();
   cardReader.PCD_Init();  
   delay(500);
   cardReader.PCD_DumpVersionToSerial();
}

void resetCoinCounter() { coins_count = 0; }

bool readCoinsAmount() {
  static int price = iAqua::eeprom::readPrice();
  if (coins_count >= price) {
    return true;
  } else {
    return false;
  }
}

byte* readCard() {
  const int uuid_size = 4;
  byte* UID_readed = new byte[uuid_size];
  if (cardReader.PICC_IsNewCardPresent()) {
    if (cardReader.PICC_ReadCardSerial()) {
      Serial.println("Card UID");
      for (byte i = 0; i < cardReader.uid.size; i++) {
        Serial.print(cardReader.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(cardReader.uid.uidByte[i]);
        UID_readed[i] = cardReader.uid.uidByte[i];
      }
    }
    Serial.println(" ");
  }
  else{
    for( int i=0; i<uuid_size; i++){
    UID_readed[i] = 0x00;
    }
  }
  return UID_readed;
}

bool verifyCard(){
  static unsigned long current_time = 0;
  const int new_read = 1000;
  const int uuid_size = 4;

  if(millis()< current_time + new_read){
    return false;
  }
  Serial.println("verifying...");

  byte* card_readed = readCard();
  if(card_readed[0] == 0 && card_readed[1] == 0 && card_readed[2] == 0 && card_readed[3] == 0){
    delete[] card_readed;
    current_time = millis();
    return false;
  }
  Serial.println("card not 0");

  byte* storaged_uuid = iAqua::eeprom::readCardUID();

  for(int i = 0; i < uuid_size; i++){
    Serial.println(String(card_readed[i]) + " " + String(storaged_uuid[i]));
    if(card_readed[i] != storaged_uuid[i]){
      iAqua::screen::printScreenTwoLines("Tarjeta", LINE_1, "invalida", LINE_2);
      Serial.println("Tarjeta invalida");
      delay(delay_message);
      delete[] storaged_uuid;
      current_time = millis();
      return false;
    }
  }
  Serial.println("correct read?");
  delete[] card_readed;
  delete[] storaged_uuid;
  current_time = millis();
  
  return true;
}

void relunchRFID(){
  static int relunchTime = 10 * 1000;
  static bool timerStart = 0;
  static unsigned long previousTimeToRelunchRFIF = 0;

  if ((millis() - previousTimeToRelunchRFIF) >= relunchTime)
  {
    cardReader.PCD_Init();
    delay(4);
    previousTimeToRelunchRFIF = millis();
  }
}

} // namespace payment
} // namespace iAqua