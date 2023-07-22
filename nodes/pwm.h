/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#ifndef MBED_NODES_PWM_H
#define MBED_NODES_PWM_H MBED_NODES_PWM_H

#include "mbed.h"

namespace mbed_nodes{

//@node: auto
struct pwm{
    PinName param_pin = NC;
    int param_period_us = 1000;
    float in;
    
    PwmOut* pin;
    
    void init();
    void tick();
};

} // namespace mbed_nodes

#endif // MBED_NODES_PWM_H
