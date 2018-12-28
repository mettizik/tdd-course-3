#include <cstring>
#include "__socket.h"
#include "socketchannel.h"

namespace {
    void SocketClose(int* fd)
    {
        if (fd && *fd > 0) {
            socket_close(*fd);
        }
    }

    std::shared_ptr<int> GuardSockFd(int fd)
    {
        if (fd < 0) {
            throw NetworkError("Bad socket fd!");
        }
        return std::shared_ptr<int>(new int(fd), SocketClose);
    }
}

void SocketChannel::Bind(uint16_t port)
{
    if (fd_ && *fd_ > 0) {
        throw NetworkError("Socket already initialized");
    }

    fd_ = GuardSockFd(socket_create(port));
}

void SocketChannel::Connect(const std::string& addr, uint16_t port)
{
    if (fd_ && *fd_ > 0) {
        throw NetworkError("Socket already initialized");
    }

    fd_ = GuardSockFd(socket_connect(addr.c_str(), port));
}

void SocketChannel::Accept()
{
    if (nullptr == fd_ || *fd_ <= 0) {
        throw NetworkError("Socket not initialized");
    }
    int newClient = socket_accept(*fd_, 0);
    if (newClient < 0) {
        throw NetworkError("Failed to accept inbound connect");
    }
    fd_ = GuardSockFd(newClient);
}

std::string SocketChannel::read()
{
    if (nullptr == fd_ || *fd_ <= 0) {
        throw NetworkError("Socket not initialized");
    }
    std::vector<char> buffer(4096, 0);
    auto result = socket_receive(*fd_, buffer.data(), buffer.size());
    if (result < 0) {
        throw NetworkError("Failed to receive data using network");
    }
    return std::string(buffer.cbegin(), buffer.cbegin() + result);
}

void SocketChannel::write(const std::string& message_to_send)
{
    if (nullptr == fd_ || *fd_ <= 0) {
        throw NetworkError("Socket not initialized");
    }
    std::vector<std::string::value_type> message(message_to_send.cbegin(), message_to_send.cend());
    auto result = socket_send(*fd_, message.data(), message.size());
    if (result < 0) {
        throw NetworkError("Failed to receive data using network");
    }
}
