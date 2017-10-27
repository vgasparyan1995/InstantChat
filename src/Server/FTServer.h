#pragma ocne

#include <asio.hpp>

#include "ChatRoom.h"

namespace Server {

class FTServer
{
public:
    explicit FTServer(asio::io_service& service,
                      const asio::ip::tcp::endpoint& endpoint);
private:
    void accept();

private:
    asio::ip::tcp::acceptor m_accpetor;
    asio::ip::tcp::socket   m_socket;
    FTPRoom                 m_room;
};

} // namespace Server
