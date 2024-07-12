#pragma once
#include <iostream>

// Logging function for strings
void log(const std::string& message) {
    std::cout << message << std::endl;
}

// Logging function for numbers in hexadecimal format
template <typename T>
void logHex(const std::string& message, T value) {
    std::ostringstream oss;
    oss << message << std::hex << value;
    log(oss.str());
}