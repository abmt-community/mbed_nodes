#ifndef MBED_NODES_CONTROL_H
#define MBED_NODES_CONTROL_H MBED_NODES_CONTROL_H

#include <cstdint>
#include <cmath>

namespace mbed_nodes{


//@node: auto
//@raster: 10ms
struct pt1_float{
    double out;
    double in = 0;
    double param_t = 1;
    double param_initial_value = 0;
    
    void init();
    void tick();
};

//@node: auto
//@raster: 10ms
struct pt2_float{
    double out;
    double out_derivative;
    double in = 0;
    double param_t  = 1;
    double param_d  = 1;
    double param_initial_value = 0;
    double param_initial_value_derivative = 0;
    double T_inv;
    double TT_inv;
    
    
    void init();
    void tick();
};


//@node:auto
//@raster: 10ms
class pt2_int{
public:
	int32_t out;
	int64_t mem1;
	int64_t mem2;
	int32_t in = 0;
	int32_t d_1k;
	int64_t T_inv;
	int64_t TT_inv;
	int32_t ticks_per_sec = 100;
	float param_t = 0.1;
    float param_d = 1.0;

    void init();
    void tick();
};

//@node:auto
//@raster: 10ms
class pt1_int{
public:
	int32_t out;
	int32_t in;
	float param_t = 1;
	int32_t param_initial_value;
	
	int64_t mem;
	int32_t dt_divT;

    void init();
    void tick();
};


} // namespace mbed_nodes

#endif // MBED_NODES_CONTROL_H
