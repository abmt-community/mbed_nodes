/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#include "interrupt_pin.h"

using namespace std;
using namespace mbed_nodes;

void interrupt_pin::init(){
    pin = new InterruptIn(param_pin, param_pin_mode);
    
    if(param_on_rising_edge){
        pin->rise([this]{
            count++;
            if(ready_for_irq){
                isr_flags.set(1);
                ready_for_irq = false;
            }
        });
    }
    
    if(param_on_falling_edge){
        pin->fall([this]{
            count++;
            if(ready_for_irq){
                isr_flags.set(1);
                ready_for_irq = false;
            }
        });
    }
    isr_flags.clear(1);
    ready_for_irq = true;
    if(param_sleep_time_ms > 0){
        sleep_time = abmt::time::ms(param_sleep_time_ms);
    }
}

abmt::time interrupt_pin::poll(){
    ready_for_irq = true;
    isr_flags.wait_any(1,param_wait_time_ms);
    isr_flags.clear(1);
    if(out_count != count){
        out_count = count;
        return 0;
    }
    return param_sleep_time_ms;
}
