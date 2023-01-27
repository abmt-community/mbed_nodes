#ifndef MBED_NODES_USB_CDC_H
#define MBED_NODES_USB_CDC_H MBED_NODES_USB_CDC_H

#include "mbed.h"
#include "USBCDC.h"
#include <abmt/io/buffer.h>

namespace mbed_nodes{
    
//@node:auto
struct usb_cdc{
    abmt::blob_shared in;
    abmt::blob_shared out;
    
    abmt::io::buffer buff_in;
    abmt::io::buffer buff_out;
    USBCDC* serial;
    
    void init();
    void tick();
};

} // namespace mbed_nodes

#endif // MBED_NODES_USB_CDC_H
