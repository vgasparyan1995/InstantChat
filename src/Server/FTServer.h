#pragma ocne

#include <asio.hpp>

#include "FTPRoom.h"

namespace Server {

class FTServer
{
public:
    explicit FTServer(asio::io_service& service,
                      const asio::ip::tcp::endpoint& endpoint);
private:
    void accept();

private:
    asio::ip::tcp::acceptor m_acceptor;
    asio::ip::tcp::socket   m_socket;
    FTPRoom                 m_room;
};

} // namespace Server
