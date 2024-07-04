#pragma once
#include <iostream>
#include <vector>

struct Packet {
    uint16_t head;
    uint8_t type;
    uint16_t seq;
    uint16_t len;
    std::vector<uint8_t> data;
    uint16_t crc16;
    std::string stringData;
};