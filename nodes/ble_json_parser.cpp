/**
 * Author: Hendrik van Arragon, 2023
 * SPDX-License-Identifier: MIT
 */
#include "ble_json_parser.h"

using namespace std;
using namespace mbed_nodes;

#include <abmt/os.h>

using namespace std;
using namespace mbed_nodes;


void ble_json_parser::tick(){
    buffer += in;
    abmt::json received_object;
    size_t pos = 0;
    while(pos != string::npos){
        pos = buffer.find("\n\n");
        if(pos != string::npos){
            received_object = abmt::json::parse((void*)buffer.c_str(), pos);
            handle_json(received_object);
            buffer.erase(0,pos + 2);
        }
    }
}

void ble_json_parser::handle_json(abmt::json& j){
    if(j.is_object() == false){
        return;
    }
    if(j.key_exsists("out")){
        out = j["out"];
    }
}