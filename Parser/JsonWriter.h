#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser.h"
using json = nlohmann::json;

void JSONWrite(Packet packet) {
    std::ofstream out;
    out.open("pars.json");
    std::stringstream ss;
    ss << std::hex << packet.head;
    std::string hexHead = ss.str();

    json Doc;
    Doc["Head"] = hexHead;
    Doc["Type"] = packet.type;
    Doc["Seq"] = packet.seq;
    Doc["Len"] = packet.len;
    Doc["Data"] = packet.stringData;

    out << Doc.dump(2);
    out.close();
}