/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#include "uart.h"

using namespace std;
using namespace mbed_nodes;

uart::uart():buff_in(20), buff_out(20){
    
}

void uart::init(){
    serial = new BufferedSerial(param_pin_tx, param_pin_rx, param_baudrate);
    serial->set_blocking(false);
}

void uart::tick(){
    buff_out.push_back(in.data, in.size);
    uint32_t bytes_send = 0;
    if( buff_out.bytes_used > 0 && serial->writable() ){
        bytes_send = serial->write(buff_out.data, buff_out.bytes_used);
    }
    buff_out.pop_front(bytes_send);

    uint32_t bytes_read = 0;
    do{
        if( buff_in.size < buff_in.bytes_used + 20 ){
            buff_in.set_size(buff_in.bytes_used + 20);
        }
        
        if( serial->readable() ){
            bytes_read = serial->read(buff_in.data + buff_in.bytes_used, buff_in.size - buff_in.bytes_used);
        }else{
            break;
        }
        
        buff_in.bytes_used += bytes_read;
    } while(bytes_read > 0);
    out.realloc(buff_in.data, buff_in.bytes_used);
    buff_in.flush();
}