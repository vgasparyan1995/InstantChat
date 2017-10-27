#include <asio.hpp>

#include "FTSession.h"

namespace Server {

FTSession::FTSession(asio::ip::tcp::socket&& socket, FTPRoom& room)
    : m_socket(std::move(socket))
    , m_room(room)
{
}

void FTSession::start()
{
    m_room.join(shared_from_this());
    readHeader();
}

void FTSession::deliver(const Generic::FilePackage& msg)
{
    auto isWriteInPorgress = !m_filesToSend.empty();
    m_filesToSend.push_back(msg);
    if (!isWriteInPorgress) {
        writeOne();
    }
}

void FTSession::readHeader()
{
    auto self(shared_from_this());
    auto buf = asio::buffer(m_lastReceivedFile.getRawData(),
                            Generic::FilePackage::s_headerSize);
    asio::async_read(m_socket, buf,
                     [this, self] (std::error_code ec, size_t)
                     {
                         if (ec) {
                             m_room.leave(shared_from_this());
                             return;
                         }
                         m_lastReceivedFile.decodeHeader();
                         readBody();
                     });
}

void FTSession::readBody()
{
    auto self(shared_from_this());
    const auto headerSize = Generic::FilePackage::s_headerSize;
    auto buf = asio::buffer(m_lastReceivedFile.getRawData() + headerSize,
                            m_lastReceivedFile.getLength());
    asio::async_read(m_socket, buf,
                     [this, self] (std::error_code ec, size_t)
                     {
                         if (ec) {
                             m_room.leave(shared_from_this());
                             return;
                         }
                         m_room.deliver(m_lastReceivedFile);
                         readHeader();
                     });
}

void FTSession::writeOne()
{
    auto self(shared_from_this());
    const auto headerSize = Generic::FilePackage::s_headerSize;
    const auto file = m_filesToSend.front();
    auto buf = asio::buffer(file.getRawData(), file.getLength() + headerSize);
    asio::async_write(m_socket, buf,
            [this, self] (std::error_code ec, size_t)
            {
                if (ec) {
                    m_room.leave(shared_from_this());
                    return;
                }
                m_filesToSend.pop_front();
                if (!m_filesToSend.empty()) {
                    writeOne();
                }
            });
}

} // namespace Server
