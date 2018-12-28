#include "client.h"

#include "chat.h"

Client::Client(std::shared_ptr<IOChannel> in, std::shared_ptr<IOChannel> out)
    : ChatParticipant (in, out)
{}

std::string Client::DoHandshake(const std::string &nickname)
{
    return MakeClientHandshake(nickname, *outChannel_);
}
