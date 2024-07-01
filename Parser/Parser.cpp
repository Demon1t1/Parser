#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
using json = nlohmann::json;


const uint16_t HEAD = 0x2424;

enum PacketType {
    LOGIN = 0,
    DATA = 1,
    KEEP_ALIVE = 2
};

struct Packet {
    uint16_t head;
    uint8_t type;
    uint16_t seq;
    uint16_t len;
    std::vector<uint8_t> data;
    uint16_t crc16;
    string stringData;
    
    void parse(std::vector<uint8_t> buffer) {
        //std::cout << "Buffer size: " << std::dec << buffer.size() << std::endl;

        size_t offset = 0;

        // Чтение head
        head = buffer[offset] | (buffer[offset + 1] << 8);
        offset += 2;
        std::cout << "Head: " << std::hex << head << std::endl;
        if (head != 0x2424) {
            throw std::runtime_error("Invalid head");
        }

        // Чтение type
        type = buffer[offset];
        offset += 1;
        std::cout << "Type: " << std::hex << static_cast<int>(type) << std::endl;
        
        // Чтение seq
        seq = buffer[offset] | (buffer[offset + 1] << 8);
        offset += 2;
        std::cout << "Seq: " << std::hex << seq << std::endl;

        // Чтение len
        len = buffer[offset] | (buffer[offset + 1] << 8);
        offset += 2;
        std::cout << "Len: " << std::hex << len << std::endl;

        // Чтение data
        data.resize(len);
        char dataChar[sizeof(data)];
        memcpy(dataChar, &buffer[offset], len);
        offset += len;
        std::cout << "Data: ";
        for (int i = 0; i < len; i++) {
            std::cout << dataChar[i];
            stringData += dataChar[i];
        }

        //std::ofstream out;
        //out.open("pars.json");
        //if (out.is_open()) {
        //    out << "{" << std::endl;
        //    out << "\t\"Head\": \"" << std::hex << head << "\"," << std::endl;
        //    out << "\t\"Type\": \"" << std::hex << static_cast<int>(type) << "\"," << std::endl;
        //    out << "\t\"Seq\": \"" << std::hex << seq << "\"," << std::endl;
        //    out << "\t\"Len\": \"" << std::hex << len << "\"," << std::endl;
        //    out << "\t\"Data\": \"";
        //    for (int i = 0; i < len; i++) {
        //        out << dataChar[i];
        //    }
        //    out << "\"" << std::endl;
        //    out << "}" << std::endl;
        //}
        //out.close();
    }

    void JSONWrite() {
        std::ofstream out;
        out.open("pars.json");
        std::stringstream ss;
        ss << std::hex << head;
        std::string hexHead = ss.str();

        json Doc;
        Doc["Head"] = hexHead;
        Doc["Type"] = type;
        Doc["Seq"] = seq;
        Doc["Len"] = len;
        Doc["Data"] = stringData;

        out << Doc.dump(2);
        out.close();
    }
    
};

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
    packet.parse(buffer);
    packet.JSONWrite();
}

//for (int i = 0; i < sizeof(head); i++)
        //{
        //    //char b[sizeof(head)];
        //    //memcpy(b, buffer, sizeof(head));
        //    uint16_t b = buffer[i];
        //    cout << b;
        //}