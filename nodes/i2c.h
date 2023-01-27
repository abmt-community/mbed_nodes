#ifndef MBED_NODES_I2C_H
#define MBED_NODES_I2C_H MBED_NODES_I2C_H


#include <abmt/os.h>
#include <abmt/time.h>
#include <abmt/io/i2c.h>
#include <abmt/mutex.h>
#include "mbed.h"

namespace mbed_nodes{

#ifdef DEVICE_I2C
struct i2c_bus_mbed: public abmt::io::i2c_bus{
    I2C device;
    abmt::mutex mutex;
    
    i2c_bus_mbed(PinName sda, PinName scl, int baud): device(sda,scl){
        device.frequency(baud);
    }
    abmt::time last_err_send = 0;
    
    virtual bool write_read(uint16_t addr, void* write, uint16_t w_len, void* read, uint16_t r_len){
		bool ok = false;

		uint8_t adr = addr << 1;

		if(w_len > 0){
			bool read_after_write = false;
			if(r_len > 0){
				read_after_write = true;
			}
			ok = device.write(adr,(char*) write,w_len, read_after_write);
		}
		if(r_len > 0){
			ok = device.read(adr, (char*) read, r_len);
		}
		if(ok == 0){
		    return true;
		}
		if( last_err_send + abmt::time::sec(3) < abmt::time::now() ){
		    abmt::os::log("I2C: unable to connect to id " + std::to_string(addr) + " [dec].");
		    last_err_send = abmt::time::now();
		}
		return false;
    }
};

#ifndef I2C_SDA
#define I2C_SDA NC
#endif

#ifndef I2C_SCL
#define I2C_SCL NC
#endif

//@node: auto
struct i2c{
	abmt::io::i2c_bus_ptr out_i2c_bus;
	int param_baudrate = 400000;
	PinName param_pin_sda = I2C_SDA;
	PinName param_pin_scl = I2C_SCL;
    void init(){
        out_i2c_bus.reset(new i2c_bus_mbed(param_pin_sda, param_pin_scl, param_baudrate));
    }
};

#endif

} // namespace mbed_nodes

#endif // MBED_NODES_I2C_H
