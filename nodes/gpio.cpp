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
}

void gpio_input::tick(){
    out = *pin;
}