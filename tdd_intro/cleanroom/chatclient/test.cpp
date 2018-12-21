#include <gmock/gmock.h>

using namespace testing;
/*
Implement chat application, that communicates via TCP sockets.
 There is list of requirenments to this application:
 * It receives user nickname through commandline arguments on start
 * It runs only for two clients
 * On start it checks if port 4444 is bound
    * if it is - connects to other client
    * if not - binds a port and waits for inbound connection
        * message "No one is here..." is displayed in UI
 * After establishing connection - handshake is performed:
    * client writes message with it's nickname and ':HELLO!' string to socket ("client:HELLO!")
    * server responses with it's nickname and ':HELLO!' magic ("server:HELLO!")
        * if server receives malformated message - it drops connection with this client
        * if client receives malformated message - it drops connection and exits
            * Error message is shown
    * Listening socket must be closed
        (i) More than one client is not allowed to connect

 * It must send messages via created connection, until it is dropped
    * Application outputs "me: " prefix for user input
    * User inputs message through console interface and presses ENTER
    * Text message is sent to socket
 * It must receive messages via created connection, until it is dropped
    * Message received through socket
    * Line with message and '@friend_name: ' prefix is displayed ("metizik: Hello!")
 * END of message is determined by '\0' byte
 * When connection is dropped by one of users
    * "You are alone now" message is displayed to user
    * Application exits

  (i) Client starts dialog

 OPTIONAL requirement:
    * If user enters '!exit!' message, application must close connection and exit
    * If user runs app with 'me' nickname - error with text "Username me is reserved and can not be used" is displayed and application exits
*/

/*
void main(argc, argv) {

}
*/

#include <gmock/gmock.h>

#include "uichannel.h"
#include "chat.h"



class MockIOChannel: public IOChannel
{
public:
    MockIOChannel()
    {
        ON_CALL(*this, read()).WillByDefault(Throw(TerminateException("")));
    }

    MOCK_METHOD0(read, std::string());
    MOCK_METHOD1(write, void(const std::string&));
};


TEST(Chat, MessagesAreExchangedInTwoDirections)
{
    MockIOChannel inputChannel;
    MockIOChannel outputChannel;

    EXPECT_CALL(inputChannel, read()).WillOnce(Return("test"));
    EXPECT_CALL(outputChannel, write("test"));
    EXPECT_CALL(outputChannel, read()).WillOnce(Return("test2"));
    EXPECT_CALL(inputChannel, write("test2"));

    ExchangeMessage(inputChannel, outputChannel);
}

TEST(Chat, UIShowsPrompt)
{
    std::stringstream inputStream;
    std::stringstream outputStream;
    UIChannel uiChannel(outputStream, inputStream);
    uiChannel.read();
    EXPECT_EQ("me: ", outputStream.str());
}

TEST(Chat, ReadReturnsUserInput)
{
    std::stringstream outputStream;
    std::stringstream inputStream("hello");
    UIChannel uiChannel(outputStream, inputStream);
    EXPECT_EQ("hello", uiChannel.read());
}

TEST(Chat, ReadReturnsUserInputWithSpaces)
{
    std::stringstream outputStream;
    std::stringstream inputStream("hello world");
    UIChannel uiChannel(outputStream, inputStream);
    EXPECT_EQ("hello world", uiChannel.read());
}

TEST(Chat, WriteUserMessageToOutput)
{
    std::stringstream outputStream;
    std::stringstream inputStream;
    UIChannel uiChannel(outputStream, inputStream);

    uiChannel.write("hello");
    std::string messages = outputStream.str();

    EXPECT_NE(std::string::npos, messages.find("hello"));
}

TEST(Chat, UIChannelWritesUsernameWithMessage)
{
    std::stringstream outputStream;
    std::stringstream inputStream;
    UIChannel uiChannel(outputStream, inputStream);
    uiChannel.setBuddy("bob");

    uiChannel.write("hello");

    EXPECT_EQ("bob: hello", outputStream.str());
}

TEST(Chat, UIChannelWritesUnknownUsernameWithMessageWhnUsernameIsNotSet)
{
    std::stringstream outputStream;
    std::stringstream inputStream;
    UIChannel uiChannel(outputStream, inputStream);

    uiChannel.write("hello");

    EXPECT_EQ("unknown: hello", outputStream.str());
}

TEST(Chat, ExchangeLoopExitsOnExitCommandFromUIChannel)
{
    //function should return on !exit!
    //no send to output

    MockIOChannel inputChannel;
    MockIOChannel outputChannel;

    EXPECT_CALL(inputChannel, read()).WillOnce(Throw(TerminateException("")));
    EXPECT_CALL(outputChannel, write(::testing::_)).Times(0);

    ExchangeMessage(inputChannel, outputChannel);
}

TEST(Chat, ExchangesMessagesUntilExit)
{
    //function should return on !exit!
    //no send to output

    MockIOChannel inputChannel;
    MockIOChannel outputChannel;

    {
        InSequence inSequence;

        EXPECT_CALL(inputChannel, read()).WillOnce(Return("test"));
        EXPECT_CALL(outputChannel, write(::testing::_));
        EXPECT_CALL(outputChannel, read()).WillOnce(Return("test2"));
        EXPECT_CALL(inputChannel, write(::testing::_));

        EXPECT_CALL(inputChannel, read()).WillOnce(Throw(TerminateException("")));
        EXPECT_CALL(outputChannel, write(::testing::_)).Times(0);
    }

    ExchangeMessage(inputChannel, outputChannel);
}

TEST(Chat, UIChannelThrowsTerminateExceptionOnExit)
{
    std::stringstream outputStream;
    std::stringstream inputStream("!exit!");
    UIChannel uiChannel(outputStream, inputStream);
    EXPECT_THROW(uiChannel.read(), TerminateException);
}

TEST(Chat, ClientHandshakeSendCorrectHandshakeMessage)
{
    MockIOChannel outputChannel;

    EXPECT_CALL(outputChannel, write("roma" + handshakeTag));
    ON_CALL(outputChannel, read()).WillByDefault(Return("max" + handshakeTag));

    MakeClientHandshake("roma", outputChannel);
}

TEST(Chat, ClientHandshakeReadCorrectServerNick)
{
    MockIOChannel outputChannel;

    ON_CALL(outputChannel, read()).WillByDefault(Return("max" + handshakeTag));

    EXPECT_EQ("max", MakeClientHandshake("roma", outputChannel));
}

TEST(Chat, ClientHandshakeFailsOnIncorrectServerResponse)
{
    MockIOChannel outputChannel;

    ON_CALL(outputChannel, read()).WillByDefault(Return("maxHELLO!"));

    EXPECT_THROW(MakeClientHandshake("roma", outputChannel), std::exception);
}

TEST(Chat, ClientHandshakeSuccessfulIfBuddyNicknameHasColons)
{
    MockIOChannel outputChannel;

    ON_CALL(outputChannel, read()).WillByDefault(Return("m:a:x" + handshakeTag));

    EXPECT_EQ("m:a:x", MakeClientHandshake("roma", outputChannel));
}

TEST(Chat, ServerHandshakeReadsClientHandshake)
{
    MockIOChannel outputChannel;

    ON_CALL(outputChannel, read()).WillByDefault(Return("max" + handshakeTag));

    EXPECT_EQ("max", MakeServerHandshake("roma", outputChannel));
}

TEST(Chat, ServerHandshakeWritesNameToClient)
{
    MockIOChannel outputChannel;

    ON_CALL(outputChannel, read()).WillByDefault(Return("max" + handshakeTag));
    EXPECT_CALL(outputChannel, write("roma" + handshakeTag));

    MakeServerHandshake("roma", outputChannel);
}

TEST(Chat, FabricReturnedClient)
{
    MockSocket socket;

    ON_CALL(socket, setup_server()).WillByDeafult(Throw(std::exception()));

    Fabric fabric(socket);
    auto client = fabric.create();

    EXPECT_NE(dynamic_cast<Client>(client), nullptr);
}

// auto ui_channel;
// auto fabric = Fabric(ui_channel);
// auto me = fabric.create(addr, port);
// me.handshake();
// me.exchange_mess();
