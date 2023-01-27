#ifndef MBED_NODES_INTERRUPT_PIN_H
#define MBED_NODES_INTERRUPT_PIN_H MBED_NODES_INTERRUPT_PIN_H

#include "mbed.h"

namespace mbed_nodes{

//@node: auto
//@raster: source
struct interrupt_pin{
    uint32_t out_count = 0;
    
    PinName param_pin = NC;
    PinMode param_pin_mode = PullDefault;
    bool param_on_rising_edge  = true;
    bool param_on_falling_edge = false;
    osPriority_t param_priority = osPriorityNormal2;
    
    InterruptIn* pin;
    EventFlags isr_flags;
    volatile uint32_t count = 0;
    volatile bool read_for_irq = true;
    
    void init();
    bool poll();
    
};

} // namespace mbed_nodes

#endif // MBED_NODES_INTERRUPT_PIN_H
