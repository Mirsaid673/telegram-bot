#include <stdio.h>
#include <tgbot/tgbot.h>
#include "token.h"
#include "utf.h"
#include "picture_downloader.h"

int main()
{
    TgBot::Bot bot(token);

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message)
                              { bot.getApi().sendMessage(message->chat->id, "Hi, this bot was made by Mirsaid!"); });

    bot.getEvents().onCommand("print", [&bot](TgBot::Message::Ptr message)
                              { bot.getApi().sendMessage(message->chat->id, "you used comand print"); });

    bot.getEvents().onCommand("help", [&bot](TgBot::Message::Ptr message)
                              { bot.getApi().sendMessage(message->chat->id, "I love you"); });

    bot.getEvents().onNonCommandMessage([&bot](TgBot::Message::Ptr message)
                                        { bot.getApi().sendPhoto(message->chat->id,
                                                                 getPictureUrl(message->text)); });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message)
                                 { std::cout << message->chat->firstName + ": " + message->text << std::endl; });
    try
    {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true)
        {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (TgBot::TgException &e)
    {
        printf("error: %s\n", e.what());
    }
    return 0;
}