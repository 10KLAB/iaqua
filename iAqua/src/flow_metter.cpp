#include "flow_metter.h"
#include "FlowMeter.h"
#include "digital_io.h"
#include "screen_mananger.h"


#define FLOWMETTER_1 20

namespace iAqua {
namespace flowMetter {
FlowMeter *Meter1;
void Meter1ISR() { Meter1->count(); }
void setupFlowMetter() {
  Meter1 = new FlowMeter(digitalPinToInterrupt(FLOWMETTER_1),
                         UncalibratedSensor, Meter1ISR, RISING);
}

void testFlowMetter(){
    Meter1->setTotalVolume(0.00);
    const int period = 100;
    static unsigned long currentTime = 0;
    const int refresh_screen_time = 1000;

    while(Meter1->getTotalVolume() < 5){
        Meter1->tick(period);
        Serial.println(Meter1->getTotalVolume());

        if(millis() >= currentTime + refresh_screen_time){
            iAqua::screen::printScreen("L= " + String(Meter1->getTotalVolume()), 35);
            currentTime = millis();
        }
    
    }
}

} // namespace flowmetter
} // namespace iAqua