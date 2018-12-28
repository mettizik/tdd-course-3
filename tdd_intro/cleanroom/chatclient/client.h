#ifndef CLIENT_H
#define CLIENT_H
#include "chatparticipant.h"

#include <memory>

#include <iochannel.h>

class Client : public ChatParticipant
{
public:
    Client(std::shared_ptr<IOChannel> in, std::shared_ptr<IOChannel> out);

    std::string DoHandshake(const std::string &nickname);
};

#endif // CLIENT_H
