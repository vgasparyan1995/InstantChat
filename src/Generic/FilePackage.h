#pragma once

#include <cstdlib>
#include <string>

#include "Serializers.h"

namespace Generic {

class FilePackage
{
public:
    static const int s_headerSize = sizeof(size_t);

public:
    FilePackage();

    size_t              getLength()     const;
    std::string         getFilename()   const;
    const ByteArray&    getFile()       const;
    const Byte*         getRawData()    const;

    Byte*   getRawData();
    void    setFilename(const std::string& filename);
    void    setFile(ByteArray&& file);
    void    encode();
    void    decode();
    void    decodeHeader();
    void    decodeBody();

private:
    size_t      m_length;
    std::string m_filename;
    ByteArray   m_file;
    ByteArray   m_rawData;
};

} // namespace Generic
