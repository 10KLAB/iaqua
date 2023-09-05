#include <Arduino.h>
#ifndef DIGITAL_IO_H_
#define DIGITAL_IO_H_
namespace iAqua{
    namespace digitalIO{
        void setupIO();
        void testButtons();
        bool readButton(int button);
        void testValves();
        void testRelays();
    }
    
}


#endif