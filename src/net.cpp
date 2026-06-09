#include "net.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include <QDebug>

bool Net::isNetExists = false;

Net::Net(const std::string& address, unsigned short port)
    : io_context_()
    , socket_(nullptr)
    , server_address_(address)
    , server_port_(port)
{
    if(!isNetExists) isNetExists = true;
    else
    {
        qDebug() << "==========SINGLETON==========";
        Net::~Net();
    }
}

Net::~Net()
{
    Disconnect();
}

bool Net::Connect()
{
    if (IsConnected())
    {
        return true;
    }
    
    try
    {
        socket_ = std::make_unique<tcp::socket>(io_context_);
        tcp::resolver resolver(io_context_);
        
        socket_->open(tcp::v4());
        socket_->set_option(boost::asio::socket_base::reuse_address(true));
        
        boost::system::error_code ec;
        auto endpoints = resolver.resolve(server_address_, 
                                        std::to_string(server_port_), ec);
        
        if (ec)
        {
            std::cerr << "Connect: Resolve error: " << ec.message() << std::endl;
            CleanupSocket();
            return false;
        }
        
        boost::asio::connect(*socket_, endpoints, ec);
        
        if (ec)
        {
            std::cerr << "Connect: Connection error: " << ec.message() << std::endl;
            CleanupSocket();
            return false;
        }
        
        std::cout << "Successfully connected to server" << std::endl;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Connect: Exception: " << e.what() << std::endl;
        CleanupSocket();
        return false;
    }
}

void Net::Disconnect()
{
    if (!IsConnected())
    {
        return;
    }
    
    try
    {
        boost::system::error_code ec;
        socket_->shutdown(tcp::socket::shutdown_both, ec);
        socket_->close(ec);
        std::cout << "Disconnected from server" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Disconnect: Exception: " << e.what() << std::endl;
    }
    
    CleanupSocket();
}

bool Net::IsConnected() const
{
    return socket_ && socket_->is_open();
}

bool Net::RequestUpdates(const std::string& update_dir)
{
    if (!IsConnected())
    {
        std::cerr << "RequestUpdates: Not connected to server" << std::endl;
        return false;
    }
    
    try
    {
        fs::create_directories(update_dir);
        
        std::cout << "Requesting updates from server..." << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (!SendRequest("GET_UPDATES"))
        {
            std::cerr << "Failed to send update request" << std::endl;
            return false;
        }
        
        std::cout << "Request sent, waiting for server response..." << std::endl;
        
        std::vector<std::string> files;
        if (!ReceiveFileList(files))
        {
            std::cerr << "Failed to receive file list" << std::endl;
            return false;
        }
        
        if (files.empty())
        {
            std::cout << "No updates available" << std::endl;
            SendRequest("UPDATES_COMPLETE");
            return true;
        }
        
        std::cout << "Receiving " << files.size() << " update files:" << std::endl;
        
        for (const auto& filename : files)
        {
            std::cout << "  Receiving: " << filename << " ... ";
            
            if (!ReceiveFile(filename, update_dir))
            {
                std::cerr << "FAILED" << std::endl;
                return false;
            }
            std::cout << "OK" << std::endl;
        }
        
        std::cout << "Sending completion confirmation..." << std::endl;
        SendRequest("UPDATES_COMPLETE");
        
        std::cout << "All updates received successfully!" << std::endl;
        
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "RequestUpdates: Exception: " << e.what() << std::endl;
        return false;
    }
}

bool Net::SendRequest(const std::string& request)
{
    try
    {
        boost::system::error_code ec;
        
        uint32_t request_size = request.size();
        std::cout << "Sending request: " << request << " (size: " << request_size << ")" << std::endl;
        
        boost::asio::write(*socket_, boost::asio::buffer(&request_size, sizeof(request_size)), ec);
        
        if (ec)
        {
            std::cerr << "SendRequest: Failed to send size: " << ec.message() << std::endl;
            return false;
        }
        
        boost::asio::write(*socket_, boost::asio::buffer(request), ec);
        
        if (ec)
        {
            std::cerr << "SendRequest: Failed to send request: " << ec.message() << std::endl;
            return false;
        }
        
        std::cout << "Request sent successfully" << std::endl;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "SendRequest: Exception: " << e.what() << std::endl;
        return false;
    }
}

bool Net::ReceiveFileList(std::vector<std::string>& files)
{
    try
    {
        boost::system::error_code ec;
        
        std::cout << "Waiting for file list..." << std::endl;
        
        uint32_t file_count = 0;
        size_t bytes_read = boost::asio::read(*socket_, boost::asio::buffer(&file_count, sizeof(file_count)), ec);
        
        if (ec)
        {
            if (ec == boost::asio::error::eof)
            {
                std::cerr << "ReceiveFileList: Connection closed by server" << std::endl;
            }
            else
            {
                std::cerr << "ReceiveFileList: Failed to receive count: " << ec.message() << std::endl;
            }
            return false;
        }
        
        std::cout << "Server has " << file_count << " files" << std::endl;
        
        for (uint32_t i = 0; i < file_count; ++i)
        {
            uint32_t name_length = 0;
            boost::asio::read(*socket_, boost::asio::buffer(&name_length, sizeof(name_length)), ec);
            
            if (ec)
            {
                std::cerr << "ReceiveFileList: Failed to receive name length: " << ec.message() << std::endl;
                return false;
            }
            
            std::vector<char> name_buffer(name_length);
            boost::asio::read(*socket_, boost::asio::buffer(name_buffer, name_length), ec);
            
            if (ec)
            {
                std::cerr << "ReceiveFileList: Failed to receive filename: " << ec.message() << std::endl;
                return false;
            }
            
            std::string filename(name_buffer.begin(), name_buffer.end());
            files.push_back(filename);
            std::cout << "  File: " << filename << std::endl;
        }
        
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "ReceiveFileList: Exception: " << e.what() << std::endl;
        return false;
    }
}

bool Net::ReceiveFile(const std::string& filename, const std::string& save_dir)
{
    try
    {
        boost::system::error_code ec;
        
        uint64_t file_size = 0;
        boost::asio::read(*socket_, boost::asio::buffer(&file_size, sizeof(file_size)), ec);
        
        if (ec)
        {
            std::cerr << "ReceiveFile: Failed to receive file size: " << ec.message() << std::endl;
            return false;
        }
        
        std::cout << "File size: " << file_size << " bytes" << std::endl;
        
        fs::path save_path = fs::path(save_dir) / filename;
        
        fs::create_directories(save_path.parent_path());
        std::ofstream output_file(save_path, std::ios::binary);
        if (!output_file.is_open())
        {
            std::cerr << "ReceiveFile: Failed to create file: " << save_path << std::endl;
            if (file_size > 0)
            {
                std::vector<char> dummy(file_size);
                boost::asio::read(*socket_, boost::asio::buffer(dummy), ec);
            }
            return false;
        }
        
        const size_t chunk_size = 8192;
        std::vector<char> buffer(chunk_size);
        uint64_t remaining = file_size;
        
        while (remaining > 0)
        {
            size_t to_read = std::min(static_cast<uint64_t>(chunk_size), remaining);
            size_t bytes_read = boost::asio::read(*socket_, 
                boost::asio::buffer(buffer.data(), to_read), ec);
            
            if (ec)
            {
                std::cerr << "ReceiveFile: Failed to read file data: " << ec.message() << std::endl;
                output_file.close();
                return false;
            }
            
            output_file.write(buffer.data(), bytes_read);
            remaining -= bytes_read;
            
            if (file_size > 1024 * 1024)
            {
                float progress = (1.0f - (float)remaining / file_size) * 100.0f;
                std::cout << "\r  Progress: " << std::fixed << std::setprecision(1) << progress << "%";
            }
        }
        
        if (file_size > 1024 * 1024)
        {
            std::cout << std::endl;
        }
        
        output_file.close();
        
        SendRequest("FILE_RECEIVED");
        
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "ReceiveFile: Exception: " << e.what() << std::endl;
        return false;
    }
}

void Net::CleanupSocket()
{
    if (socket_)
    {
        socket_.reset();
    }
}

QString Net::RequestVersion()
{
    if (!IsConnected())
    {
        qDebug() << "RequestVersion: Not connected to server";
        return QString();
    }
    
    try
    {
        if (!SendRequest("GET_VERSION"))
        {
            qDebug() << "Failed to send version request";
            return QString();
        }
        
        uint32_t dataSize = 0;
        boost::system::error_code ec;
        boost::asio::read(*socket_, boost::asio::buffer(&dataSize, sizeof(dataSize)), ec);
        
        if (ec)
        {
            qDebug() << "Failed to receive version data size:" << ec.message().c_str();
            return QString();
        }
        
        std::vector<char> buffer(dataSize);
        boost::asio::read(*socket_, boost::asio::buffer(buffer, dataSize), ec);
        
        if (ec)
        {
            qDebug() << "Failed to receive version data:" << ec.message().c_str();
            return QString();
        }
        
        QString version = QString::fromUtf8(buffer.data(), dataSize);
        qDebug() << "Received version:" << version;
        
        return version;
    }
    catch (const std::exception& e)
    {
        qDebug() << "RequestVersion exception:" << e.what();
        return QString();
    }
}