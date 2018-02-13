#ifndef FILEUTILS_HPP
#define FILEUTILS_HPP

#include <string>
#include <fstream>
#include <iterator>

class FileUtils {
public:
    static std::string  LoadFile(std::string const &path);
};

#endif