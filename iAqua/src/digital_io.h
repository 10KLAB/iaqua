#include <Arduino.h>
#ifndef DIGITAL_IO_H_
#define DIGITAL_IO_H_
namespace iAqua{
    namespace digitalIO{
        void setupIO();
        void setValve(int valve, bool state);
        void testButtons();
        bool readButton(int button);
        bool selectYesOrNo();
        void waitLeftButton(int button);
        void testValves();
        void testRelays();
        void testDoor();
        void doorDown();
        void doorUp();
        void stopDoor();
    }
    
}


#endif