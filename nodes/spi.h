/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#ifndef MBED_NODES_SPI_H
#define MBED_NODES_SPI_H MBED_NODES_SPI_H

#include <abmt/io/spi.h>
#include "mbed.h"

namespace mbed_nodes{

//@node: auto
struct spi{
	
	PinName param_pin_mosi = NC;
	PinName param_pin_miso = NC;
	PinName param_pin_sck  = NC;
	int param_baudrate = 1000000;
	int param_mode = 0; /// bit1 = pol, bit2 = pah; google
	
	
	abmt::io::spi_ptr out_spi_bus;
	
    void init();
};


} // namespace mbed_nodes

#endif // MBED_NODES_SPI_H
