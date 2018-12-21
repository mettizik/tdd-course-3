#ifndef UICHANNEL_H
#define UICHANNEL_H

#include "iochannel.h"
#include "chat.h"

#include <iostream>

class UIChannel : public IOChannel
{
public:
    UIChannel(std::ostream& outputStream, std::istream& inputStream);

    void setBuddy(const std::string& buddyName);

    // IOChannel interface
public:
    std::string read();
    void write(const std::string &message);

private:
    std::ostream& outputStream_;
    std::istream& inputStream_;
    std::string buddyName_ = "unknown";
};

#endif // UICHANNEL_H
