#pragma once

#include <iostream>

#include <cstdlib>
#include <string>

#include "Serializers.h"

namespace Generic {

class ChatMessage
{
public:
    static const int s_headerSize = sizeof(size_t);

public:
    ChatMessage();

    size_t      getLength()     const;
    std::string getSender()     const;
    std::string getText()       const;
    const Byte* getRawData()    const;

    Byte*   getRawData();
    void    setSender(const std::string& sender);
    void    setText(const std::string& text);
    void    encode();
    void    decode();
    void    decodeHeader();
    void    decodeBody();

private:
    size_t      m_length;
    std::string m_sender;
    std::string m_text;
    ByteArray   m_rawData;
};

} // namespace Generic
