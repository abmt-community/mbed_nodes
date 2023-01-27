#ifndef MBED_NODES_ANALOG_OUTPUT_H
#define MBED_NODES_ANALOG_OUTPUT_H MBED_NODES_ANALOG_OUTPUT_H

#include "mbed.h"

namespace mbed_nodes{

//@node: auto
struct analog_output{
    PinName param_pin = NC;
    float in;
    
    AnalogOut* pin;
    
    void init();
    void tick();
};

} // namespace mbed_nodes

#endif // MBED_NODES_ANALOG_OUTPUT_H
