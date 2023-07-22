/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */

#ifndef MBED_NODES_I2C_H
#define MBED_NODES_I2C_H MBED_NODES_I2C_H


#include <abmt/os.h>
#include <abmt/time.h>
#include <abmt/io/i2c.h>
#include <abmt/mutex.h>
#include "mbed.h"

namespace mbed_nodes{

#ifdef DEVICE_I2C

#ifndef I2C_SDA
#define I2C_SDA NC
#endif

#ifndef I2C_SCL
#define I2C_SCL NC
#endif

//@node: auto
struct i2c{
	abmt::io::i2c_ptr out_i2c_bus;
	int param_baudrate = 400000;
	PinName param_pin_sda = I2C_SDA;
	PinName param_pin_scl = I2C_SCL;
    void init();
};

#endif

} // namespace mbed_nodes

#endif // MBED_NODES_I2C_H
