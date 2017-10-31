#include <fstream>
#include <iterator>

#include "FileUtils.h"

namespace Generic {
namespace FileUtils {

std::string removeDir(const std::string& filename)
{
    const auto pos = filename.find_last_of('/');
    return filename.substr(pos + 1);
}

bool saveFile(const FilePackage& file)
{
    std::basic_ofstream<Byte> outFileStream(file.getFilename().c_str(), std::ios::out | std::ios::binary);
    if (!outFileStream.good()) {
        return false;
    }
    std::copy(file.getFile().begin(),
              file.getFile().end(),
              std::ostreambuf_iterator<Byte>(outFileStream));
    return true;
}

ByteArray readFile(const std::string& filename)
{
    ByteArray result;
    std::ifstream inFileStream(filename.c_str(), std::ios::binary | std::ios::in);
    if (!inFileStream.good()) {
        return result;
    }
    std::copy(std::istreambuf_iterator<Byte>(inFileStream),
              std::istreambuf_iterator<Byte>(),
              std::back_inserter(result));
    return result;
}

} // namespace FileUtils
} // namespace Generic
