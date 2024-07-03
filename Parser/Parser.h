#pragma once
#include <iostream>
#include <vector>
#include "Packet.h"


Packet parse(std::vector<uint8_t> buffer, Packet packet) {

    size_t offset = 0;

    // Read head
    packet.head = buffer[offset] | (buffer[offset + 1] << 8);
    offset += 2;
    std::cout << "Head: " << std::hex << packet.head << std::endl;
    if (packet.head != 0x2424) {
        throw std::runtime_error("Invalid head");
    }

    // Read type
    packet.type = buffer[offset];
    offset += 1;
    std::cout << "Type: " << std::hex << static_cast<int>(packet.type) << std::endl;

    // Read seq
    packet.seq = buffer[offset] | (buffer[offset + 1] << 8);
    offset += 2;
    std::cout << "Seq: " << std::hex << packet.seq << std::endl;

    // Read len
    packet.len = buffer[offset] | (buffer[offset + 1] << 8);
    offset += 2;
    std::cout << "Len: " << std::hex << packet.len << std::endl;

    // Read data
    packet.data.resize(packet.len);
    char dataChar[sizeof(packet.data)];
    memcpy(dataChar, &buffer[offset], packet.len);
    offset += packet.len;
    std::cout << "Data: ";
    for (int i = 0; i < packet.len; i++) {
        std::cout << dataChar[i];
        packet.stringData += dataChar[i];
    }
    return packet;
}