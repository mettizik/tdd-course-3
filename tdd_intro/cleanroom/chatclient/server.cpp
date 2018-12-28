#include "server.h"
#include "chat.h"

Server::Server(std::shared_ptr<IOChannel> in, std::shared_ptr<IOChannel> out)
    : ChatParticipant (in, out)
{

}

std::string Server::DoHandshake(const std::string &nickname)
{
    return MakeServerHandshake(nickname, *outChannel_);
}
