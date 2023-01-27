#ifndef MBED_NODES_ANALOG_INPUT_H
#define MBED_NODES_ANALOG_INPUT_H MBED_NODES_ANALOG_INPUT_H

#include "mbed.h"

namespace mbed_nodes{

//@node: auto
struct analog_input{
    PinName param_pin = NC;
    float out;
    
    AnalogIn* pin;
    
    void init();
    void tick();
};

} // namespace mbed_nodes

#endif // MBED_NODES_ANALOG_INPUT_H
