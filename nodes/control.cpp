#include "control.h"

using namespace std;
using namespace mbed_nodes;

void pt1_float::init(){
    out = param_initial_value;
}

void pt1_float::tick(){
    out = out + 0.01/param_t * (in - out);
}


void pt2_float::init(){
    double T = 1.0/2.0/M_PI*param_t;
    T_inv    = 1.0/T;
    TT_inv   = 1.0/(T*T);
    out      = param_initial_value;
    out_derivative = param_initial_value_derivative;
}

void pt2_float::tick(){
    out_derivative = out_derivative + 0.01 * (in*TT_inv - out*TT_inv - out_derivative*2*param_d*T_inv);
    out += 0.01 * out_derivative;
}

void pt2_int::init(){
	d_1k = param_d*1024;
    float T  = 1.0/2.0/M_PI*param_t;
    T_inv    = 1.0/T + 0.5;
    TT_inv   = 1.0/(T*T) + 0.5;
    mem2 = 0;
    mem1 = in*16*ticks_per_sec;
}

void pt2_int::tick(){
    mem2 += (in*16*TT_inv - mem1*TT_inv/ticks_per_sec - mem2*2*d_1k*T_inv/1024)/ticks_per_sec;
    mem1 += mem2;
    out = mem1/16/ticks_per_sec;
}

void pt1_int::init(){
    out = param_initial_value;
    mem = out * 1024;
    dt_divT = 0.01/param_t*1024 + 0.5;
}

void pt1_int::tick(){
    mem = mem + (dt_divT * (in - out));
    out = mem / 1024;
}