#include <iostream>
#include <vector>
#include "JsonWriter.h"
using namespace std;

int main()
{
    std::vector<uint8_t> buffer = {
        0x24, 0x24,  // head
        0x01,        // type (Data)
        0x01, 0x00,  // seq
        0x05, 0x00,  // len
        0x48, 0x65, 0x6c, 0x6c, 0x6f  // data ("Hello")
    };
    Packet packet;
    packet = parse(buffer, packet);
    JSONWrite(packet);
}