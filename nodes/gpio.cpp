/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */
#include "gpio.h"

using namespace std;
using namespace mbed_nodes;

void gpio_output::init(){
    pin = new DigitalOut(param_pin);
}

void gpio_output::tick(){
    *pin = in;
}


void gpio_input::init(){
    pin = new DigitalIn(param_pin);
    if(param_pull_down){
        pin->mode(PullDown);
    }else if(param_pull_up){
        pin->mode(PullUp);
    }else if(param_pull_none){
        pin->mode(PullNone);
    }else if(param_pull_open){
        pin->mode(OpenDrain);
    }
}

void gpio_input::tick(){
    out = *pin;
}