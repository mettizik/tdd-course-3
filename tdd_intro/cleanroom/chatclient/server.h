#ifndef SERVER_H
#define SERVER_H
#include "chatparticipant.h"

#include <memory>
#include "iochannel.h"

class Server : public ChatParticipant
{
public:
    Server(std::shared_ptr<IOChannel> in, std::shared_ptr<IOChannel> out);

    virtual std::string DoHandshake(const std::string& nickname);
};

#endif // SERVER_H
