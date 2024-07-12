#pragma once
#include <iostream>
#include <vector>
#include "Packet.h"
#include "Log.h"

Packet parse(std::vector<uint8_t> buffer, Packet packet) {

    size_t offset = 0;

    // Read head
    packet.head = buffer[offset] | (buffer[offset + 1] << 8);
    offset += 2;
    logHex("Head: ", packet.head);

    // Read type
    packet.type = buffer[offset];
    offset += 1;
    log("Type: " + std::to_string(packet.type));

    // Read seq
    packet.seq = buffer[offset] | (buffer[offset + 1] << 8);
    offset += 2;
    logHex("Seq: ", packet.seq);

    // Read len
    packet.len = buffer[offset] | (buffer[offset + 1] << 8);
    offset += 2;
    logHex("Len: ", packet.len);

    // Read data
    packet.data.resize(packet.len);
    char dataChar[sizeof(packet.data)];
    memcpy(dataChar, &buffer[offset], packet.len);
    offset += packet.len;
    for (int i = 0; i < packet.len; i++) {
        packet.stringData += dataChar[i];
    }
    logHex("Data: ", packet.stringData);
    return packet;
}