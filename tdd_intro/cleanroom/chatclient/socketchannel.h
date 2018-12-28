#ifndef SOCKET_H
#define SOCKET_H
#include <stdexcept>
#include <vector>
#include <memory>
#include "iochannel.h"

class SocketChannel : public IOChannel
{
public:
    virtual void Bind(uint16_t port);
    virtual void Connect(const char* addr, uint16_t port);
    virtual void Accept();

    std::string read();
    void write(const std::string &message);

private:
    std::shared_ptr<int> fd_ = nullptr;
};

using NetworkError = std::runtime_error;

#endif // SOCKET_H
