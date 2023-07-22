/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#include "spi.h"

#include <abmt/os.h>

using namespace std;
using namespace mbed_nodes;

struct mbed_spi_bus: public abmt::io::spi{
    SPI device;
    mbed_spi_bus(PinName mosi, PinName miso, PinName clk, int baud, int mode): device(mosi,miso,clk){
        device.frequency(baud);
        device.format(8, mode);
    }
    
    virtual uint8_t tranceive(uint8_t data){
        return device.write(data);
	}
};

void spi::init(){
        out_spi_bus.reset(new mbed_spi_bus(param_pin_mosi, param_pin_miso, param_pin_sck, param_baudrate, param_mode));
}