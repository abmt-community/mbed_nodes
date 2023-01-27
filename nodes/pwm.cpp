#include "pwm.h"

using namespace std;
using namespace mbed_nodes;

    void pwm::init(){
        pin = new PwmOut(param_pin);
        pin->period_us(param_period_us);
    }
    
    void pwm::tick(){
        if(in > 1){
            in = 1;
        }
        if(in < 0){
            in = 0;
        }
        pin->write(in);
    }