#include <gtest/gtest.h>
#include <socketchannel.h>

TEST(Socket, DISABLED_SocketBindDoesNotThrowOnFirstBind)
{
    SocketChannel io;
    EXPECT_NO_THROW(io.Bind(4444));
}

TEST(Socket, DISABLED_SocketBindThrowsOnSecondBind)
{
    SocketChannel io;
    io.Bind(8888);
    EXPECT_THROW(io.Bind(4444), NetworkError);
}

TEST(Socket, DISABLED_SocketBindThrowsWhenAddressIsBOund)
{
    SocketChannel io1;
    io1.Bind(4444);
    SocketChannel io;
    EXPECT_THROW(io.Bind(4444), NetworkError);
}

TEST(Socket, DISABLED_SocketConnectThrowsWhenNoServerExists)
{
    SocketChannel io;
    EXPECT_THROW(io.Connect("localhost", 4444), NetworkError);
}

/*
TEST(Socket, DISABLED_BindAndAcceptRealExternalClient)
{
    SocketChannel io1;
    io1.Bind(4444);
    io1.Accept();
    io1.write("Wtf???");
    EXPECT_FALSE(io1.read().empty());
}
*/
