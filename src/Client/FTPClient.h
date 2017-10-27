#pragma once

#include <queue>

#include <asio.hpp>

#include "Generic/FilePackage.h"

namespace Client {

using FilePackageQueue = std::queue<Generic::FilePackage>;

class FTPClient
{
public:
    explicit FTPClient(asio::io_service& service,
                       asio::ip::tcp::resolver::iterator endpointIter);
    void send(const Generic::FilePackage& file);
    void close();

private:
    void connect(asio::ip::tcp::resolver::iterator endpointIter);
    void readHeader();
    void readBody();
    void sendOne();

private:
    asio::io_service&       m_service;
    asio::ip::tcp::socket   m_socket;
    Generic::FilePackage    m_lastReceivedFile;
    FilePackageQueue        m_filesToSend;
};

} // namespace Client
