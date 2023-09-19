#include <Arduino.h>
#include "U8g2lib.h"
#include <SPI.h>
#include <Wire.h>
#ifndef SCREEN_MANANGER_H_
namespace iAqua{
    namespace screen{
        void setupScreen();
        void printScreen(String text, int line);
        void printScreenTwoLines(String text1, int line1, String text2, int line2);
    }
    
}
#endif