#include "chat.h"

namespace
{
    std::string ParseHandshakeMessage(const std::string& serverMessage)
    {
        auto helloBegin = serverMessage.find(handshakeTag);
        if(helloBegin == std::string::npos)
        {
            throw std::runtime_error("Server answered wrong.");
        }
        return serverMessage.substr(0, helloBegin);
    }
}

void ForwardMessage(IOChannel& inputChannel, IOChannel& outputChannel)
{
    auto msg = inputChannel.read();
    outputChannel.write(msg);
}

void ExchangeMessage(IOChannel& inputChannel, IOChannel& outputChannel)
{
    while (true)
    {
        try
        {
            ForwardMessage(inputChannel, outputChannel);
            ForwardMessage(outputChannel, inputChannel);
        }
        catch(const TerminateException&)
        {
            return;
        }
    }
}

std::string MakeClientHandshake(const std::string& clientName, IOChannel& outputChannel)
{
    outputChannel.write(clientName + handshakeTag);
    auto serverMessage = outputChannel.read();
    return ParseHandshakeMessage(serverMessage);
}

std::string MakeServerHandshake(const std::string& clientName, IOChannel& outputChannel)
{
    auto serverMessage = outputChannel.read();
    auto hand_massage = ParseHandshakeMessage(serverMessage);
    outputChannel.write(clientName + handshakeTag);
    return hand_massage;
}
