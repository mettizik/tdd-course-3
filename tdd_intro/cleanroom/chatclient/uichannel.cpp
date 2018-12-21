#include "uichannel.h"

UIChannel::UIChannel(std::ostream &outputStream, std::istream &inputStream)
    : outputStream_(outputStream)
    , inputStream_(inputStream)
{

}

void UIChannel::setBuddy(const std::string &buddyName)
{
    buddyName_ = buddyName;
}

std::string UIChannel::read()
{
    outputStream_ << "me: ";

    std::string message;
    std::getline(inputStream_, message);

    if(message == "!exit!")
    {
        throw TerminateException("user canceled");
    }

    return message;
}

void UIChannel::write(const std::string &message)
{
    outputStream_ << buddyName_ << ": " << message;
}
