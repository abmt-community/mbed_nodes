#ifndef MBED_NODES_GPIO_H
#define MBED_NODES_GPIO_H MBED_NODES_GPIO_H

#include "mbed.h"

namespace mbed_nodes{

//@node: auto
struct gpio_output{
    PinName param_pin = NC;
    bool in;
    
    DigitalOut* pin;
    
    void init();
    void tick();
};

//@node: auto
struct gpio_input{
    PinName param_pin = NC;
    bool out;
    
    DigitalIn* pin;
    
    void init();
    void tick();
};

} // namespace mbed_nodes

#endif // MBED_NODES_GPIO_H
