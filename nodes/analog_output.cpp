#include "analog_output.h"

using namespace std;
using namespace mbed_nodes;

void analog_output::init(){
    pin = new AnalogOut(param_pin);
}

void analog_output::tick(){
    *pin = in;
}