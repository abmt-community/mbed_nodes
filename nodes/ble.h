#ifndef MBED_TEST_BLE_H
#define MBED_TEST_BLE_H MBED_TEST_BLE_H

#include <string>
#include "mbed.h"

namespace mbed_test{

//@node: auto
struct ble{
    std::string out;
    std::string in;
    bool out_connected = false;

    std::string param_name = "ABMT-BLE";
    uint16_t param_service_uuid = 0xA000;
    uint16_t param_rcv_uuid = 0xA001;
    uint16_t param_snd_uuid = 0xA002;
    
    /**
     * mtu can be changed in mbed_app.json.
     * quick test: your data should fit in 4 packages.
     * very old devices only support 20 bytes.
     * I had problems sending packages larger then 63 bytes.
     */
    const uint16_t mtu = MBED_CONF_CORDIO_DESIRED_ATT_MTU - 4; 
    
    void* com;
    std::string last_send = "";

    void init();
    void tick();
};

} // namespace mbed_test

#endif // MBED_TEST_BLE_H
auto