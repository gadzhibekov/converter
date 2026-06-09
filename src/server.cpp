#include "server.h"
#include <iostream>

Server::Server(boost::asio::io_context& io_context, short port,
             const std::string& update_data_dir)
    : io_context_(io_context)
    , acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
    , update_data_dir_(update_data_dir)
{
    fs::create_directories(update_data_dir_);
    
    std::cout << "Server started on port " << port << std::endl;
    std::cout << "Serving updates from: " << fs::absolute(update_data_dir_) << std::endl;
}

void Server::Start()
{
    StartAccept();
}

void Server::StartAccept()
{
    auto socket = std::make_shared<tcp::socket>(io_context_);
    
    acceptor_.async_accept(*socket,
        [this, socket](const boost::system::error_code& error)
        {
            if (!error)
            {
                std::cout << "New client connected from: " 
                         << socket->remote_endpoint() << std::endl;
                
                std::thread(&Server::HandleClient, this, socket).detach();
            }
            else
            {
                std::cerr << "Accept error: " << error.message() << std::endl;
            }
            
            StartAccept();
        });
}

void Server::HandleClient(std::shared_ptr<tcp::socket> socket)
{
    try
    {
        while (true)
        {
            std::string request;
            
            if (!ReceiveRequest(socket, request))
            {
                std::cerr << "Failed to receive request or connection closed" << std::endl;
                break;
            }
            
            std::cout << "Received request: " << request << std::endl;
            
            if (request == "GET_UPDATES")
            {
                std::vector<std::string> files = GetUpdateFiles();
                
                if (!SendFileList(socket, files))
                {
                    std::cerr << "Failed to send file list" << std::endl;
                    break;
                }
                
                for (const auto& filename : files)
                {
                    std::cout << "Sending file: " << filename << std::endl;
                    
                    if (!SendFile(socket, filename))
                    {
                        std::cerr << "Failed to send file: " << filename << std::endl;
                        break;
                    }
                    
                    std::string ack;
                    if (!ReceiveRequest(socket, ack) || ack != "FILE_RECEIVED")
                    {
                        std::cerr << "Failed to receive acknowledgment for: " << filename << std::endl;
                        break;
                    }
                }
                
                std::string complete_msg;
                if (ReceiveRequest(socket, complete_msg) && complete_msg == "UPDATES_COMPLETE")
                {
                    std::cout << "Update completed successfully" << std::endl;
                }
            }
            else if (request == "GET_VERSION")
            {
                HandleVersionRequest(socket);
            }
            else if (request == "DISCONNECT")
            {
                std::cout << "Client requested disconnect" << std::endl;
                break;
            }
            else
            {
                std::cout << "Unknown request: " << request << std::endl;
                break;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "HandleClient: Exception: " << e.what() << std::endl;
    }
    
    std::cout << "Closing client connection..." << std::endl;
    
    boost::system::error_code ec;
    socket->shutdown(tcp::socket::shutdown_both, ec);
    socket->close(ec);
}

bool Server::ReceiveRequest(std::shared_ptr<tcp::socket> socket, std::string& request)
{
    try
    {
        boost::system::error_code ec;
        
        uint32_t request_size = 0;
        boost::asio::read(*socket, boost::asio::buffer(&request_size, sizeof(request_size)), ec);
        
        if (ec)
        {
            std::cerr << "ReceiveRequest: Failed to read size: " << ec.message() << std::endl;
            return false;
        }
        
        std::vector<char> buffer(request_size);
        boost::asio::read(*socket, boost::asio::buffer(buffer, request_size), ec);
        
        if (ec)
        {
            std::cerr << "ReceiveRequest: Failed to read request: " << ec.message() << std::endl;
            return false;
        }
        
        request = std::string(buffer.begin(), buffer.end());
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "ReceiveRequest: Exception: " << e.what() << std::endl;
        return false;
    }
}

bool Server::SendFileList(std::shared_ptr<tcp::socket> socket, 
                         const std::vector<std::string>& files)
{
    try
    {
        boost::system::error_code ec;
        
        uint32_t file_count = files.size();
        boost::asio::write(*socket, boost::asio::buffer(&file_count, sizeof(file_count)), ec);
        
        if (ec)
        {
            std::cerr << "SendFileList: Failed to send count: " << ec.message() << std::endl;
            return false;
        }
        
        for (const auto& filename : files)
        {
            uint32_t name_length = filename.size();
            boost::asio::write(*socket, boost::asio::buffer(&name_length, sizeof(name_length)), ec);
            
            if (ec)
            {
                std::cerr << "SendFileList: Failed to send name length: " << ec.message() << std::endl;
                return false;
            }
            
            boost::asio::write(*socket, boost::asio::buffer(filename), ec);
            
            if (ec)
            {
                std::cerr << "SendFileList: Failed to send filename: " << ec.message() << std::endl;
                return false;
            }
        }
        
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "SendFileList: Exception: " << e.what() << std::endl;
        return false;
    }
}

bool Server::SendFile(std::shared_ptr<tcp::socket> socket, const std::string& filename)
{
    try
    {
        boost::system::error_code ec;
        
        fs::path file_path = fs::path(update_data_dir_) / filename;
        
        if (!fs::exists(file_path))
        {
            std::cerr << "SendFile: File not found: " << file_path << std::endl;
            return false;
        }
        
        uint64_t file_size = fs::file_size(file_path);
        
        boost::asio::write(*socket, boost::asio::buffer(&file_size, sizeof(file_size)), ec);
        
        if (ec)
        {
            std::cerr << "SendFile: Failed to send file size: " << ec.message() << std::endl;
            return false;
        }
        
        std::ifstream input_file(file_path, std::ios::binary);
        if (!input_file.is_open())
        {
            std::cerr << "SendFile: Failed to open file: " << file_path << std::endl;
            return false;
        }
        
        const size_t chunk_size = 8192;
        std::vector<char> buffer(chunk_size);
        
        while (input_file.read(buffer.data(), chunk_size) || input_file.gcount() > 0)
        {
            size_t bytes_to_send = input_file.gcount();
            
            if (bytes_to_send > 0)
            {
                boost::asio::write(*socket, 
                    boost::asio::buffer(buffer.data(), bytes_to_send), ec);
                
                if (ec)
                {
                    std::cerr << "SendFile: Failed to send file data: " << ec.message() << std::endl;
                    input_file.close();
                    return false;
                }
            }
        }
        
        input_file.close();
        std::cout << "File sent successfully: " << filename << std::endl;
        
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "SendFile: Exception: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::string> Server::GetUpdateFiles()
{
    std::vector<std::string> files;
    
    try
    {
        for (const auto& entry : fs::recursive_directory_iterator(update_data_dir_))
        {
            if (fs::is_regular_file(entry.path()))
            {
                fs::path relative_path = fs::relative(entry.path(), update_data_dir_);
                files.push_back(relative_path.string());
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "GetUpdateFiles: Exception: " << e.what() << std::endl;
    }
    
    return files;
}

void Server::HandleVersionRequest(std::shared_ptr<tcp::socket> socket)
{
    try
    {
        std::string versionFilePath = update_data_dir_ + "/version.txt";
        
        std::ifstream file(versionFilePath);
        if (!file.is_open())
        {
            std::cerr << "Failed to open version.txt" << std::endl;
            return;
        }
        
        std::string version;
        std::getline(file, version);
        file.close();
        
        version.erase(0, version.find_first_not_of(" \t\r\n"));
        version.erase(version.find_last_not_of(" \t\r\n") + 1);
        
        std::cout << "Sending version: " << version << std::endl;
        
        uint32_t dataSize = version.size();
        
        boost::system::error_code ec;
        boost::asio::write(*socket, boost::asio::buffer(&dataSize, sizeof(dataSize)), ec);
        
        if (ec)
        {
            std::cerr << "Failed to send version size: " << ec.message() << std::endl;
            return;
        }
        
        boost::asio::write(*socket, boost::asio::buffer(version.data(), dataSize), ec);
        
        if (ec)
        {
            std::cerr << "Failed to send version data: " << ec.message() << std::endl;
            return;
        }
        
        std::cout << "Version sent successfully" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "HandleVersionRequest exception: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[])
{
    try
    {
        short port = 12345;
        std::string update_dir = "../update_data";
        
        if (argc > 1)
        {
            port = static_cast<short>(std::atoi(argv[1]));
        }
        if (argc > 2)
        {
            update_dir = argv[2];
        }
        
        std::cout << "=== Update Server ===" << std::endl;
        std::cout << "Starting on port " << port << std::endl;
        std::cout << "Serving files from: " << update_dir << std::endl;
        std::cout << "Press Ctrl+C to stop" << std::endl;
        
        boost::asio::io_context io_context;
        Server server(io_context, port, update_dir);
        server.Start();
        
        std::vector<std::thread> threads;
        unsigned int thread_count = std::thread::hardware_concurrency();
        if (thread_count == 0) thread_count = 2;
        
        for (unsigned int i = 0; i < thread_count; ++i)
        {
            threads.emplace_back([&io_context]()
            {
                io_context.run();
            });
        }
        
        for (auto& thread : threads)
        {
            thread.join();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Server error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}