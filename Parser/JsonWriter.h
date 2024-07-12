#pragma once
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser.h"

using namespace rapidjson;

void JSONWrite(Packet packet) {
    // Creating a JSON document
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    
    std::stringstream ss;
    ss << std::hex << packet.head;
    std::string hexHead = ss.str();

    // Adding data to a JSON document
    rapidjson::Value packetJSON(rapidjson::kObjectType);
    packetJSON.AddMember("Head", rapidjson::Value().SetString(hexHead.c_str(), allocator), allocator);  
    packetJSON.AddMember("Type", packet.type, allocator);
    packetJSON.AddMember("Seq", packet.seq, allocator);
    packetJSON.AddMember("Len", packet.len, allocator);
    packetJSON.AddMember("Data", rapidjson::Value().SetString(packet.stringData.c_str(), allocator), allocator);
    document.AddMember("Packet", packetJSON, allocator);

    // Serializing a JSON document into a string
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    // JSON string output
    std::ofstream ofs("Pars.json");
    if (ofs.is_open()) {
        ofs << buffer.GetString();
        ofs.close();
        std::cout << "The JSON document has been successfully written to the Pars.json file" << std::endl;
    }
    else {
        std::cerr << "Error when opening a file for recording" << std::endl;
    }
}