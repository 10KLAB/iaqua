#include <Arduino.h>
#ifndef PAYMENT_H_
#define PAYMENT_H_

namespace iAqua{
    namespace payment{
        void setupPayment();
        byte* readCard();
        bool verifyCard();
        void relunchRFID();
        bool readCoinsAmount();

    }
}

#endif