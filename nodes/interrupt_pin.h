/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#ifndef MBED_NODES_INTERRUPT_PIN_H
#define MBED_NODES_INTERRUPT_PIN_H MBED_NODES_INTERRUPT_PIN_H

#include "mbed.h"
#include <abmt/time.h>

namespace mbed_nodes{

//@node: auto
//@raster: source
struct interrupt_pin{
    uint32_t out_count = 0;
    
    PinName param_pin = NC;
    PinMode param_pin_mode = PullDefault;
    bool param_on_rising_edge  = true;
    bool param_on_falling_edge = false;

    uint32_t param_wait_time_ms  = 1000;
    uint32_t param_sleep_time_ms = 0;
    abmt::time sleep_time = 1;
    
    InterruptIn* pin;
    EventFlags isr_flags;
    volatile uint32_t count = 0;
    volatile bool ready_for_irq = true;
    
    void init();
    abmt::time poll();
    
};

} // namespace mbed_nodes

#endif // MBED_NODES_INTERRUPT_PIN_H
