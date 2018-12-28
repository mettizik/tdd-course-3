#ifndef CHATPARTICIPANT_H
#define CHATPARTICIPANT_H
#include <memory>

class ChatParticipant
{
public:
    virtual std::string DoHandshake(const std::string& nickname) { return nickname; }
    virtual void ExchangeMessages() {}
};

using ChatParticipantGuard = std::unique_ptr<ChatParticipant>;

#endif // CHATPARTICIPANT_H
