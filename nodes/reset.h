#ifndef MBED_NODES_RESET_H
#define MBED_NODES_RESET_H MBED_NODES_RESET_H

#include "mbed.h"

namespace mbed_nodes{

//@node: auto
inline void reset(bool in_bool){
    if(in_bool){
        NVIC_SystemReset();
    }
}

} // namespace mbed_nodes

#endif // MBED_NODES_RESET_H
