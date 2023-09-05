#include <Arduino.h>
#include "U8g2lib.h"
#include <SPI.h>
#include <Wire.h>
#include "HCSR04.h"
#ifndef TEST_H_
namespace iAqua{
    namespace startTest{
        void setupScreen();
        void helloWorld(); 
        void setupButtons();
        void buttonsTest();
        void hcsrTest();
    }
}

#endif