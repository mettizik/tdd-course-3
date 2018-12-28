#include "fabric.h"
#include "server.h"
#include "client.h"

Fabric::Fabric(std::shared_ptr<IOChannel> ui)
{
}

ChatParticipantGuard Fabric::create(std::shared_ptr<SocketChannel> socket)
{
    return nullptr;
}
