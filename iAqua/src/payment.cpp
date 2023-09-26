#include "payment.h"
#include "EEPROM_magager.h"
#include "MFRC522.h"
#include <SPI.h>
#include <Wire.h>


#define COIN_COUNTER 2

#define RST_PIN 49 // Reset
#define SS_PIN 48  // SDA
// SCK=52/MOSI=51/MISO=50

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

bool readCard() {
    byte UID_readed[4] = {0, 0, 0, 0};
  if (cardReader.PICC_IsNewCardPresent()) {
    if (cardReader.PICC_ReadCardSerial()) {
      Serial.println("Card UID");
      for (byte i = 0; i < cardReader.uid.size; i++) {
        Serial.print(cardReader.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(cardReader.uid.uidByte[i], HEX);
        UID_readed[i] = cardReader.uid.uidByte[i];
      }
    }
  }
}

// bool readUID()
// {
//   bool correctTarget = false;

//   if (mfrc522.PICC_IsNewCardPresent())
//   {
//     if (mfrc522.PICC_ReadCardSerial())
//     {
//       Serial.println(F("Card UID"));
//       for (byte i = 0; i < mfrc522.uid.size; i++)
//       {
//         Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//         Serial.print(mfrc522.uid.uidByte[i], HEX);
//         actualUID[i] = mfrc522.uid.uidByte[i];
//       }
//       Serial.println("");
//     }

//     correctTarget = compareUsers();
//     if (correctTarget == true)
//     {
//       // Serial.println("reproducir selección servicio");
//       // myDFPlayer.play(3);//seleccione el servicio
//       coinsCounter = serviceValue3;
//     }
//     else if (correctTarget == false)
//     {
//       Serial.println("reproducir tarjeta invalida");
//       myDFPlayer.play(4); // tarjeta invalida
//       invalidCard();
//       delay(2000);
//     }
//     clearUID();
//   }
//   return correctTarget;
// }

} // namespace payment
} // namespace iAqua