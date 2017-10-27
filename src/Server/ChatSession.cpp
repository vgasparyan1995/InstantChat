#include <asio.hpp>

#include "ChatSession.h"

namespace Server {

ChatSession::ChatSession(asio::ip::tcp::socket&& socket, ChatRoom& room)
    : m_socket(std::move(socket))
    , m_room(room)
{
}

void ChatSession::start()
{
    m_room.join(shared_from_this());
    readHeader();
}

void ChatSession::deliver(const Generic::ChatMessage& msg)
{
    auto isWriteInPorgress = !m_messagesToWrite.empty();
    m_messagesToWrite.push_back(msg);
    if (!isWriteInPorgress) {
        writeOne();
    }
}

void ChatSession::readHeader()
{
    auto self(shared_from_this());
    auto buf = asio::buffer(m_lastReadMessage.getRawData(),
                            Generic::ChatMessage::s_headerSize);
    asio::async_read(m_socket, buf,
                     [this, self] (std::error_code ec, size_t)
                     {
                         if (ec) {
                             m_room.leave(shared_from_this());
                             return;
                         }
                         m_lastReadMessage.decodeHeader();
                         readBody();
                     });
}

void ChatSession::readBody()
{
    auto self(shared_from_this());
    const auto headerSize = Generic::ChatMessage::s_headerSize;
    auto buf = asio::buffer(m_lastReadMessage.getRawData() + headerSize,
                            m_lastReadMessage.getLength());
    asio::async_read(m_socket, buf,
                     [this, self] (std::error_code ec, size_t)
                     {
                         if (ec) {
                             m_room.leave(shared_from_this());
                             return;
                         }
                         m_room.deliver(m_lastReadMessage);
                         readHeader();
                     });
}

void ChatSession::writeOne()
{
    auto self(shared_from_this());
    const auto headerSize = Generic::ChatMessage::s_headerSize;
    const auto msg = m_messagesToWrite.front();
    auto buf = asio::buffer(msg.getRawData(), msg.getLength() + headerSize);
    asio::async_write(m_socket, buf,
                      [this, self] (std::error_code ec, size_t)
                      {
                          if (ec) {
                              m_room.leave(shared_from_this());
                              return;
                          }
                          m_messagesToWrite.pop_front();
                          if (!m_messagesToWrite.empty()) {
                              writeOne();
                          }
                      });
}

} // namespace Server
