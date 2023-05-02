#include "interrupt_pin.h"


using namespace std;
using namespace mbed_nodes;

void interrupt_pin::init(){
    osThreadSetPriority(ThisThread::get_id(),param_priority);
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
}

bool interrupt_pin::poll(){
    ready_for_irq = true;
    isr_flags.wait_any(1);
    isr_flags.clear(1);
    out_count = count;
    return true;
}
