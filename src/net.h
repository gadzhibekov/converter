#pragma once
#ifndef NET_H
#define NET_H

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <filesystem>
#include <fstream>

#include <QString>

using boost::asio::ip::tcp;
namespace fs = std::filesystem;

class Net
{
public:
    Net(const std::string& address = "192.168.0.101", unsigned short port = 12345);
    ~Net();
    
    bool    Connect();
    void    Disconnect();
    bool    IsConnected() const;
    bool    RequestUpdates(const std::string& update_dir = "updated_data");
    QString RequestVersion();

private:
    void    CleanupSocket();
    bool    SendRequest(const std::string& request);
    bool    ReceiveFile(const std::string& filename, const std::string& save_dir);
    bool    ReceiveFileList(std::vector<std::string>& files);
    
private:
    boost::asio::io_context         io_context_;
    std::unique_ptr<tcp::socket>    socket_;
    std::string                     server_address_;
    unsigned short                  server_port_;
    static bool                     isNetExists;
};

#endif // NET_H