#include "fabric.h"
#include "server.h"
#include "client.h"

Fabric::Fabric(std::shared_ptr<IOChannel> ui)
    : ui_(ui)
{
}

ChatParticipantGuard Fabric::create(std::shared_ptr<SocketChannel> socket)
{
    try
    {
        socket->Bind(4444);
        socket->Accept();
    }
    catch (const NetworkError&)
    {
        socket->Connect("localhost", 4444);
        return ChatParticipantGuard(new Client(ui_, socket));
    }
    return ChatParticipantGuard(new Server(socket, ui_));
}
