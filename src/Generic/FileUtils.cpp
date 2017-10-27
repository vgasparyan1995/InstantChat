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

void saveFile(const FilePackage& file)
{
    std::ofstream outFileStream(file.getFilename(), std::ios::binary);
    std::copy(file.getFile().begin(),
              file.getFile().end(),
              std::ostreambuf_iterator<Byte>(outFileStream));
}

ByteArray readFile(const std::string& filename)
{
    std::ifstream inFileStream(filename, std::ios::binary);
    return ByteArray( (std::istreambuf_iterator<Byte>(inFileStream)),
                      (std::istreambuf_iterator<Byte>()));
}

} // namespace FileUtils
} // namespace Generic
