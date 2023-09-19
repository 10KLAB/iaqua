#include "Adafruit_NeoPixel.h"

#define RGB_LIGTH_PIN 38
#define LED_NUMBER 90

namespace iAqua {
namespace ligths {

Adafruit_NeoPixel ambientalStrip =
    Adafruit_NeoPixel(LED_NUMBER, RGB_LIGTH_PIN, NEO_GRB + NEO_KHZ800);

void setupLigths() {
  ambientalStrip.begin();
  ambientalStrip.setBrightness(255);
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return ambientalStrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return ambientalStrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return ambientalStrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow() {
  static unsigned long cuttent_time = 0;
  static unsigned int i = 0;
  static unsigned int j = 100;
  const int refresh_time = 250;

  if ((millis() - cuttent_time) >= refresh_time) {
    j++;
    for (i = 0; i < ambientalStrip.numPixels(); i++) {
      ambientalStrip.setPixelColor(i, Wheel((i + j) & 255));
    }
    ambientalStrip.show();
    if (j >= 255) {
      j = 0;
    }
    cuttent_time = millis();
  }
}

void oneColor(int r, int g, int b) {

  for (int i = 0; i < ambientalStrip.numPixels(); i++) {
    ambientalStrip.setPixelColor(i, r, g, b);
  }
  ambientalStrip.show();
}

void setAll(byte red, byte green, byte blue) {

  for (int i = 0; i < ambientalStrip.numPixels(); i++) {
    ambientalStrip.setPixelColor(i, red, green, blue);
  }
  ambientalStrip.show();
}

void FadeOut(byte red, byte green, byte blue) {
  const int speed = 5;
  float r, g, b;

  for (int k = 255; k >= 0; k = k - 2) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    ambientalStrip.show();
    delay(speed);
  }
}

void meteorRain(byte red, byte green, byte blue) {
  oneColor(0, 0, 0);
  const int SpeedDelay = 7;
  const byte meteorSize = 90;
  const byte meteorTrailDecay = 200;
  const bool meteorRandomDecay = true;

  for (int i = 0; i < ambientalStrip.numPixels() * 2; i++) {

    // fade brightness all LEDs one step
    // for (int j = 0; j < ambientalStrip.numPixels(); j++) {
    //   if ((!meteorRandomDecay) || (random(10) > 5)) {
    //     fadeToBlack(j, meteorTrailDecay);
    //   }
    // }

    // draw meteor
    for (int j = 0; j < meteorSize; j++) {
      if ((i - j < ambientalStrip.numPixels()) && (i - j >= 0)) {
        ambientalStrip.setPixelColor(i - j, red, green, blue);
      }
    }
    ambientalStrip.show();
    delay(SpeedDelay);
  }
}

} // namespace ligths
} // namespace iAqua