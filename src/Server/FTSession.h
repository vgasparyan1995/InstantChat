#pragma once

#include <memory>

#include <asio.hpp>

#include "FTPRoom.h"

namespace Server {

class FTSession : public FTParticipant,
                  public std::enable_shared_from_this<FTSession>
{
public:
    explicit FTSession(asio::ip::tcp::socket&& socket, FTPRoom& room);
    void start();
    void deliver(const Generic::FilePackage& msg);

private:
    void readHeader();
    void readBody();
    void writeOne();

private:
    asio::ip::tcp::socket   m_socket;
    FTPRoom&                m_room;
    Generic::FilePackage    m_lastReceivedFile;
    FilePackageQueue        m_filesToSend;
};

} // namespace Server
