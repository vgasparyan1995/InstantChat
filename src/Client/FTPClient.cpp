#include "FTPClient.h"

#include "TUIManager.h"

namespace Client {

FTPClient::FTPClient(asio::io_service& service,
                     asio::ip::tcp::resolver::iterator endpointIter)
    : m_service(service)
    , m_socket(service)
{
    connect(endpointIter);
}

void FTPClient::send(const Generic::FilePackage& file) 
{
    m_service.post([this, file] ()
            {
                bool isWriteInProgress = !m_filesToSend.empty();
                auto f = file;
                f.encode();
                m_filesToSend.push(f);
                if (!isWriteInProgress) {
                    sendOne();
                }
            });
}

void FTPClient::close()
{
    m_service.post([this] () { m_socket.close(); });
}

void FTPClient::connect(asio::ip::tcp::resolver::iterator endpointIter)
{
    asio::async_connect(m_socket, endpointIter,
            [this] (std::error_code ec, asio::ip::tcp::resolver::iterator)
            {
                if (!ec) {
                    readHeader();
                }
            });
}

void FTPClient::readHeader()
{
    const auto headerSize = Generic::FilePackage::s_headerSize;
    auto buf = asio::buffer(m_lastReceivedFile.getRawData(), headerSize);
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
                auto file = m_lastReceivedFile;
                file.decodeBody();
                const std::string dialogText = "Receive file \'" + file.getFilename() + "\'? [y/N] ";
                if (TUIManager::getInstance().yesNoDialog(dialogText)) {
                    FileManager::getInstance().saveFile(file);
                }
                TUIManager::getInstance().showInfo("File saved");
                readHeader();
            });
}

void ChatClient::sendOne()
{
    const auto headerSize = Generic::FilePackage::s_headerSize;
    auto file = m_filesToSend.front();
    auto buf = asio::buffer(file.getRawData(), file.getLength() + headerSize);
    asio::async_write(m_socket, buf,
            [this] (std::error_code ec, size_t)
            {
                if (ec) {
                    m_socket.close();
                    return;
                }
                m_filesToSend.pop();
                if (!m_filesToSend.empty()) {
                    writeOne();
                }
            });
}

} // namespace Client
