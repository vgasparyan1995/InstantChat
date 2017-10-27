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
    std::basic_ofstream<Byte> outFileStream(file.getFilename(), std::ios::out | std::ios::binary);
    std::copy(file.getFile().begin(),
              file.getFile().end(),
              std::ostreambuf_iterator<Byte>(outFileStream));
}

ByteArray readFile(const std::string& filename)
{
    std::ifstream inFileStream(filename.c_str(), std::ios::binary);
    inFileStream.unsetf(std::ios::skipws);
    std::streampos fileSize;
    inFileStream.seekg(0, std::ios::end);
    fileSize = inFileStream.tellg();
    inFileStream.seekg(0, std::ios::beg);
    ByteArray result;
    result.reserve(fileSize);

    result.insert(result.begin(),
                  std::istream_iterator<Byte>(inFileStream),
                  std::istream_iterator<Byte>());
    return result;
}

} // namespace FileUtils
} // namespace Generic
