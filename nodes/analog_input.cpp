#include "analog_input.h"

using namespace std;
using namespace mbed_nodes;

void analog_input::init(){
    pin = new AnalogIn(param_pin);
}

void analog_input::tick(){
    out = *pin;
}