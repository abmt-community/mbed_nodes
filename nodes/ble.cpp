/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */
#include "ble.h"

#include <abmt/os.h>

#include <events/mbed_events.h>
#include "ble/BLE.h"
#include "ble_process.h"

using namespace std;
using namespace mbed_nodes;

struct ble_com: ble::GattServer::EventHandler{
    std::string received_data = "";
    
    EventQueue event_queue;
    ::ble::BLE& ble;
    BLEProcess ble_process;
    
    GattCharacteristic*  gch_snd  = nullptr;
    GattCharacteristic*  gch_rcv  = nullptr;
    
    uint16_t param_service_uuid;

    
    ble_com(std::string name, uint16_t service_uuid, uint16_t rcv_uuid, uint16_t snd_uuid, uint16_t buffer_size):ble(ble::BLE::Instance()), ble_process(event_queue, ble, name){
        param_service_uuid = service_uuid;
        
        gch_rcv = new GattCharacteristic(rcv_uuid, 
                            0, 
                            0, 
                            buffer_size, 
                            GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE
                        );
         
        gch_snd = new GattCharacteristic(snd_uuid, 
                            0, 
                            0, 
                            buffer_size, 
                            GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY 
                        );
        
        ble_process.on_init(callback(this, &ble_com::start));
        ble_process.start();
    }
    
    void start(BLE &ble_instance, events::EventQueue &event_queue)
    {
        GattCharacteristic* charTable[] = { gch_rcv, gch_snd };
        GattService example_service(param_service_uuid, charTable, 2);

        ble_instance.gattServer().addService(example_service);

        ble_instance.gattServer().setEventHandler(this);

    }
    
    virtual void onDataWritten(const GattWriteCallbackParams &params)
    {
        if ((params.handle == gch_rcv->getValueHandle())) {
            received_data += string((char*)params.data, params.len);
        }

    }
    
    void send_data(uint8_t* data, size_t size){
        ble.gattServer().write(gch_snd->getValueHandle(), data, size, false);
    }
    
};

void mbed_test::ble::init(){
    com = new ble_com(param_name, param_service_uuid, param_rcv_uuid, param_snd_uuid, mtu);
}

void mbed_test::ble::tick(){
    // todo: test with lager strings!
    auto c_ptr = (ble_com*) com;
    c_ptr->received_data = "";

    //snd
    out_connected = c_ptr->ble_process.connected;
    if(out_connected && last_send != in){
        last_send = in;
        while(in.size() > 0){
            if(in.size() <= mtu){
                c_ptr->send_data((uint8_t*)in.c_str(), in.size());
                in.clear();
            }else{
                c_ptr->send_data((uint8_t*)in.c_str(), mtu);
                in.erase(0,mtu);
                c_ptr->event_queue.dispatch_once();
            }
        }
    }
    if(!out_connected){
        last_send.clear(); // resend on connect
    }
    
    c_ptr->event_queue.dispatch_for(1ms);
    out = c_ptr->received_data;
}
