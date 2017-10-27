#include "ChatClient.h"

#include "TUIManager.h"

namespace Client {

ChatClient::ChatClient(asio::io_service& service,
                       asio::ip::tcp::resolver::iterator endpointIter)
    : m_service(service)
    , m_socket(service)
{
    connect(endpointIter);
}

void ChatClient::write(const Generic::ChatMessage& msg) 
{
    m_service.post([this, msg] ()
            {
                bool isWriteInProgress = !m_messagesToWrite.empty();
                auto m = msg;
                m.encode();
                m_messagesToWrite.push(m);
                if (!isWriteInProgress) {
                    writeOne();
                }
            });
}

void ChatClient::close()
{
    m_service.post([this] () { m_socket.close(); });
}

void ChatClient::connect(asio::ip::tcp::resolver::iterator endpointIter)
{
    asio::async_connect(m_socket, endpointIter,
            [this] (std::error_code ec, asio::ip::tcp::resolver::iterator)
            {
                if (!ec) {
                    readHeader();
                }
            });
}

void ChatClient::readHeader()
{
    const auto headerSize = Generic::ChatMessage::s_headerSize;
    auto buf = asio::buffer(m_lastReadMessage.getRawData(), headerSize);
    asio::async_read(m_socket, buf,
            [this] (std::error_code ec, size_t)
            {
                if (ec) {
                    m_socket.close();
                    return;
                }
                m_lastReadMessage.decodeHeader();
                readBody();
            });
}

void ChatClient::readBody()
{
    const auto headerSize = Generic::ChatMessage::s_headerSize;
    auto buf = asio::buffer(m_lastReadMessage.getRawData() + headerSize, m_lastReadMessage.getLength());
    asio::async_read(m_socket, buf,
            [this] (std::error_code ec, size_t)
            {
                if (ec) {
                    m_socket.close();
                    return;
                }
                auto msg = m_lastReadMessage;
                msg.decodeBody();
                TUIManager::getInstance().showReceivedMessage(msg);
                readHeader();
            });
}

void ChatClient::writeOne()
{
    const auto headerSize = Generic::ChatMessage::s_headerSize;
    auto msg = m_messagesToWrite.front();
    auto buf = asio::buffer(msg.getRawData(), msg.getLength() + headerSize);
    asio::async_write(m_socket, buf,
            [this] (std::error_code ec, size_t)
            {
                if (ec) {
                    m_socket.close();
                    return;
                }
                m_messagesToWrite.pop();
                if (!m_messagesToWrite.empty()) {
                    writeOne();
                }
            });
}

} // namespace Client
