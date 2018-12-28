#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <string>
#include <fabric.h>
#include <uichannel.h>
#include <socketchannel.h>

int main(int argc, char** argv)
{
    if (argc == 3 && argv[1] == std::string("--nickname"))
    {
        const std::string nickname = argv[2];
        auto ui = std::make_shared<UIChannel>(std::cout, std::cin);
        Fabric fabric(ui);
        auto chat_instance = fabric.create(std::make_shared<SocketChannel>());
        auto buddy = chat_instance->DoHandshake(nickname);
        ui->setBuddy(buddy);
        chat_instance->ExchangeMessages();
    }
    else
    {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}
