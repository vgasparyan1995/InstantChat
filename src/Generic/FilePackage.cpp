#include "FilePackage.h"

namespace Generic {

FilePackage::FilePackage()
    : m_length(0)
    , m_rawData(s_headerSize, 0)
{
}

size_t FilePackage::getLength() const
{
    return m_length;
}

std::string FilePackage::getFilename() const
{
    return m_filename;
}

const ByteArray& FilePackage::getFile() const
{
    return m_file;
}

const Byte* FilePackage::getRawData() const
{
    return m_rawData.c_str();
}

Byte* FilePackage::getRawData()
{
    return &m_rawData[0];
}

void FilePackage::setFilename(const std::string& filename)
{
    m_filename = filename;
}

void FilePackage::setFile(ByteArray&& file)
{
    m_file = file;
}

void FilePackage::encode()
{
    auto filenameAndFile = toByteArray(m_filename) + toByteArray(m_file);
    m_length = filenameAndFile.size();
    m_rawData = toByteArray(m_length) + filenameAndFile;
}

void FilePackage::decode()
{
    decodeHeader();
    decodeBody();
}

void FilePackage::decodeHeader()
{
    const auto* data = getRawData();
    fromByteArray(data, m_length);
    m_rawData.resize(s_headerSize + m_length);
}

void FilePackage::decodeBody()
{
    const auto* data = getRawData();
    auto position = s_headerSize;
    position += fromByteArray(data + position, m_filename);
    position += fromByteArray(data + position, m_file);
}

} // namespace Generic
