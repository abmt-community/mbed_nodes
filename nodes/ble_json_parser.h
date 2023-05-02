#ifndef MBED_NODES_BLE_JSON_PARSER_H
#define MBED_NODES_BLE_JSON_PARSER_H MBED_NODES_BLE_JSON_PARSER_H

#include <abmt/json.h>

namespace mbed_nodes{

//@node: auto
struct ble_json_parser{
    std::string in;
    float out = 0;
    
    std::string buffer;
    
    void tick();
    void handle_json(abmt::json& j);
};

} // namespace mbed_nodes

#endif // MBED_NODES_BLE_JSON_PARSER_H
