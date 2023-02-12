#include "ticker.h"

#include "../../../bare_metall_loop.h"

using namespace std;
using namespace mbed_nodes;

void ticker::init(){
    osThreadSetPriority(ThisThread::get_id(),param_priority);
    ticker = new Ticker();
    isr_flags.clear(1);
    ticker->attach_us( [this]{
        out_count++;
        isr_flags.set(1);
        bare_metall_trigger_main_loop();
    },param_period_us);
    
}

bool ticker::poll(){
    isr_flags.wait_any(1);
    isr_flags.clear(1);
    return true;
}