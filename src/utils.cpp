#include "utils.h"

Utilities::Utilities()
{

}

Utilities::~Utilities()
{

}

std::string Utilities::ReadFile(const char* path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open())
      throw std::runtime_error("Can\'t open shader file: " + std::string(path) + ".");

    std::stringstream stream;
    stream<<file.rdbuf();

    file.clear();
    file.close();
	
    return stream.str();
}