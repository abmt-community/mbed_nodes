/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#ifndef MBED_NODES_GPIO_H
#define MBED_NODES_GPIO_H MBED_NODES_GPIO_H

#include <abmt/io/pin.h>

#include "mbed.h"

namespace mbed_nodes{
    
struct mbed_ipin: public abmt::io::ipin{
    DigitalIn in;
    mbed_ipin(PinName p): in(p){
        
    }
    virtual bool get(){
		return (bool)in;
	}
};

struct mbed_opin: public abmt::io::opin{
    DigitalOut out;
    mbed_opin(PinName p): out(p){
        
    }
    virtual void set(bool val = true){
        out = val;
	}
};

//@node: auto
struct opin{
    PinName param_pin = NC;
    
    abmt::io::opin_ptr out_opin;
    void init(){
        out_opin.reset(new mbed_opin(param_pin));
    }
};

//@node: auto
struct ipin{
    PinName param_pin = NC;
    
    abmt::io::ipin_ptr out_ipin;
    void init(){
        out_ipin.reset(new mbed_ipin(param_pin));
    }
};

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
    bool param_pull_down = true;
    bool param_pull_up   = false;
    bool param_pull_none = false;
    bool param_pull_open = false;

    bool out;

    
    DigitalIn* pin;
    
    void init();
    void tick();
};

} // namespace mbed_nodes

#endif // MBED_NODES_GPIO_H
