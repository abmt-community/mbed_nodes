/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#ifndef MBED_NODES_TICKER_H
#define MBED_NODES_TICKER_H MBED_NODES_TICKER_H

#include "mbed.h"
#include <abmt/time.h>

namespace mbed_nodes{
    
//@node: auto
//@raster: source
struct ticker{
    uint32_t out_count;
    
    uint32_t param_period_us = 500;
    osPriority_t param_priority = osPriorityNormal1;
    
    Ticker* ticker;
    EventFlags isr_flags;
    
    void init();
    abmt::time poll();
};


} // namespace mbed_nodes

#endif // MBED_NODES_TICKER_H
