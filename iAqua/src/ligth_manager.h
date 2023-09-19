#include <Arduino.h>
#ifndef LIGTH_MANAGER_H_
#define LIGTH_MANAGER_H_

namespace iAqua{
    namespace ligths{
        void setupLigths();
        void rainbow();
        void oneColor(int r, int g, int b);
        void meteorRain(byte red, byte green, byte blue);
        void FadeOut(byte red, byte green, byte blue);

    }
}

#endif