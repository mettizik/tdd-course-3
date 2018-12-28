#ifndef CHATPARTICIPANT_H
#define CHATPARTICIPANT_H
#include <memory>
#include <string>
#include "iochannel.h"
#include "chat.h"
class ChatParticipant
{
public:
    ChatParticipant(std::shared_ptr<IOChannel> in, std::shared_ptr<IOChannel> out)
        : inChannel_(in)
        , outChannel_(out)
    {}

    virtual ~ChatParticipant() {}

    virtual std::string DoHandshake(const std::string& nickname) { return nickname; }
    virtual void ExchangeMessages() {ExchangeMessage(*inChannel_, *outChannel_);}

protected:
    std::shared_ptr<IOChannel> inChannel_;
    std::shared_ptr<IOChannel> outChannel_;
};

using ChatParticipantGuard = std::unique_ptr<ChatParticipant>;

#endif // CHATPARTICIPANT_H
