#include <Arduino.h>
#ifndef FLOW_METTER_H_
#define FLOW_METTER_H_

namespace iAqua {
namespace flowMetter {
    void setupFlowMetter();
    void testFlowMetter();
    void fillContainer();
    float readPressure();

}
} // namespace iAqua

#endif