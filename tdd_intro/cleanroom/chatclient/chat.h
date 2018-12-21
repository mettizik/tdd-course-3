#ifndef CHAT_H
#define CHAT_H

#include "iochannel.h"

const std::string handshakeTag = ":HELLO!";

using TerminateException = std::runtime_error;

void ForwardMessage(IOChannel& inputChannel, IOChannel& outputChannel);
void ExchangeMessage(IOChannel& inputChannel, IOChannel& outputChannel);

std::string MakeClientHandshake(const std::string& clientName, IOChannel& outputChannel);
std::string MakeServerHandshake(const std::string& clientName, IOChannel& outputChannel);

#endif // CHAT_H
