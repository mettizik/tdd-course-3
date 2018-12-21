#ifndef IOCHANNEL_H
#define IOCHANNEL_H

#include <string>

class IOChannel
{
public:
    virtual std::string read() = 0;
    virtual void write(const std::string& message) = 0;
};

#endif // IOCHANNEL_H
