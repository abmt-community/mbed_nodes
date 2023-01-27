#include "usb_cdc.h"

using namespace std;
using namespace mbed_nodes;

void usb_cdc::init(){
    serial = new USBCDC(false);
}

void usb_cdc::tick(){
    buff_out.push_back(in.data, in.size);
    uint32_t bytes_send = 0;
    if( buff_out.bytes_used > 0 && serial->ready() ){
        serial->send_nb(buff_out.data, buff_out.bytes_used, &bytes_send);
    }
    buff_out.pop_front(bytes_send);

    uint32_t bytes_read = 0;
    do{
        if( buff_in.size < buff_in.bytes_used + 20 ){
            buff_in.set_size(buff_in.bytes_used + 20);
        }
        
        if( serial->ready() ){
            serial->receive_nb(buff_in.data + buff_in.bytes_used, buff_in.size - buff_in.bytes_used, &bytes_read);
        }else{
            break;
        }
        
        buff_in.bytes_used += bytes_read;
    } while(bytes_read > 0);
    out.realloc(buff_in.data, buff_in.bytes_used);
    buff_in.flush();
}