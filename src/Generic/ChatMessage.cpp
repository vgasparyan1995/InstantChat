#include "ChatMessage.h"

namespace Generic {

ChatMessage::ChatMessage()
    : m_length(0)
    , m_rawData(s_headerSize, 0)
{
}

size_t ChatMessage::getLength() const
{
    return m_length;
}

std::string ChatMessage::getSender() const
{
    return m_sender;
}

std::string ChatMessage::getText() const
{
    return m_text;
}

const Byte* ChatMessage::getRawData() const
{
    return m_rawData.c_str();
}

Byte* ChatMessage::getRawData()
{
    return &m_rawData[0];
}

void ChatMessage::setSender(const std::string& sender)
{
    m_sender = sender;
}

void ChatMessage::setText(const std::string& text)
{
    m_text = text;
}

void ChatMessage::encode()
{
    auto senderAndText = toByteArray(m_sender) + toByteArray(m_text);
    m_length = senderAndText.size();
    m_rawData = toByteArray(m_length) + senderAndText;
}

void ChatMessage::decode()
{
    decodeHeader();
    decodeBody();
}

void ChatMessage::decodeHeader()
{
    const auto* data = getRawData();
    fromByteArray(data, m_length);
    m_rawData.resize(s_headerSize + m_length);
}

void ChatMessage::decodeBody()
{
    const auto* data = getRawData();
    auto position = s_headerSize;
    position += fromByteArray(data + position, m_sender);
    position += fromByteArray(data + position, m_text);
}

} // namespace Generic
