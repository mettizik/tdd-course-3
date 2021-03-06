#ifndef FABRIC_H
#define FABRIC_H
#include "iochannel.h"
#include "socketchannel.h"
#include "chatparticipant.h"

class Fabric
{
public:
    Fabric(std::shared_ptr<IOChannel> ui);
    ChatParticipantGuard create(std::shared_ptr<SocketChannel> socket);
private:
    std::shared_ptr<IOChannel> ui_;
};

#endif // FABRIC_H
