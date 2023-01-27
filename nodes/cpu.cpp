#include "cpu.h"

using namespace std;
using namespace mbed_nodes;

uint32_t mbed_nodes::main_loop_yield_cnt = 0;

void mbed_nodes::mbed_cpu_load_idle_hook(){
    main_loop_yield_cnt++;
}