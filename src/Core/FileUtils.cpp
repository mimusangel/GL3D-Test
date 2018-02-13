#include "FileUtils.hpp"

std::string  FileUtils::LoadFile(std::string const &path)
{
    std::ifstream ifs(path);
    return std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
}

  
  