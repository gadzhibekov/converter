#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>

using boost::asio::ip::tcp;
namespace fs = std::filesystem;

class Server
{
public:
    Server(boost::asio::io_context& io_context, short port, 
           const std::string& update_data_dir = "update_data");
    
    void Start();

private:
    void StartAccept();
    void HandleClient(std::shared_ptr<tcp::socket> socket);
    
    bool ReceiveRequest(std::shared_ptr<tcp::socket> socket, std::string& request);
    bool SendFileList(std::shared_ptr<tcp::socket> socket, 
                     const std::vector<std::string>& files);
    bool SendFile(std::shared_ptr<tcp::socket> socket, const std::string& filename);
    void HandleVersionRequest(std::shared_ptr<tcp::socket> socket);
    
    std::vector<std::string> GetUpdateFiles();
    
    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
    std::string update_data_dir_;
};

#endif // SERVER_H