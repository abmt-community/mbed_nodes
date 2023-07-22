/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */
#ifndef MBED_NODES_CPU_H
#define MBED_NODES_CPU_H MBED_NODES_CPU_H

#include "mbed.h"

namespace mbed_nodes{

/**
 *  Add the following to mbed_app.json in your
 *  rutime dir:
 *  "platform.heap-stats-enabled": true, 
 *  "platform.stack-stats-enabled": true
 */
//@node:auto
struct mbed_meminfo{
    uint32_t out_heap_free;
    uint32_t out_heap_used;
    uint32_t out_max_stack_mem_used;
    std::string out_max_stack_thread_name;
    void tick(){
        mbed_stats_heap_t heap_stats;
    	mbed_stats_heap_get(&heap_stats);
    	out_heap_used = heap_stats.current_size;
    	out_heap_free = heap_stats.reserved_size - out_heap_used;
    	out_max_stack_mem_used = 0;
    	out_max_stack_thread_name = "";
    	int cnt = osThreadGetCount();
    	mbed_stats_stack_t *stats = (mbed_stats_stack_t*) malloc(cnt * sizeof(mbed_stats_stack_t));
    	cnt = mbed_stats_stack_get_each(stats, cnt);
    	for (int i = 0; i < cnt; i++) {
    		if(out_max_stack_mem_used < stats[i].max_size){
    			const char* name = osThreadGetName((void*)stats[i].thread_id);
    			if(name[0] == 'r' || name[0] == 'a'){ // only rasters
    				out_max_stack_mem_used= stats[i].max_size;
    				out_max_stack_thread_name = name;
    			}
    		}
    	}
    	free(stats);
    }
};

extern uint32_t main_loop_yield_cnt;
void mbed_cpu_load_idle_hook();

//@node: auto
struct mbed_cpu_load{
    uint32_t param_no_load_ticks = 25000;
    
    uint32_t out_yield_ticks;
    float out_load;
    
    void init(){
        Kernel::attach_idle_hook(&mbed_cpu_load_idle_hook);
    }
    
    void tick(){
        out_yield_ticks = main_loop_yield_cnt;
        main_loop_yield_cnt = 0;
        out_load = 100 - (float)out_yield_ticks/param_no_load_ticks*100.0;
        if(out_load < 0){
            out_load = 0;
        }
        if(out_load > 100){
            out_load = 100;
        }
    }
};


//@node:auto
struct mbed_set_thread_priority{
    osPriority_t param_priority = osPriorityHigh;
    void init(){
        osThreadSetPriority(ThisThread::get_id(),param_priority);
    }
};


//@node:auto
struct mbed_test_load{
    uint32_t in_knops = 10;
    void tick(){
        for(uint32_t i = 0; i < in_knops; i++){
            for(int j = 0; j < 1000; j++){
                asm("nop;");
            }
        }  
    }
};

} // namespace mbed_nodes

#endif // MBED_NODES_CPU_H
