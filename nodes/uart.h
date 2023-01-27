#ifndef MBED_NODES_UART_H
#define MBED_NODES_UART_H MBED_NODES_UART_H

#include "mbed.h"
#include <abmt/io/buffer.h>

namespace mbed_nodes{
    
//@node:auto
struct uart{
    abmt::blob_shared in;
    abmt::blob_shared out;
    uint32_t param_baudrate = 115200;
    PinName param_pin_rx = NC;
    PinName param_pin_tx = NC;
    
    abmt::io::buffer buff_in;
    abmt::io::buffer buff_out;
    BufferedSerial* serial;
    
    uart();
    
    void init();
    void tick();
};

} // namespace mbed_nodes

#endif // MBED_NODES_UART_H
