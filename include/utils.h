#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Utilities
{
private:

public:
    Utilities();
    ~Utilities();

    // Reads content of the specified file path and returns a const char*
    static std::string ReadFile(const char* path);
};