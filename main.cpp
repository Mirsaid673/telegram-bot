#include <stdio.h>
#include <tgbot/tgbot.h>

int main()
{
    TgBot::Bot bot("TOKEN");

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message)
                              { bot.getApi().sendMessage(message->chat->id, "Hi, this bot was made by Mirsaid!"); });

    bot.getEvents().onCommand("print", [&bot](TgBot::Message::Ptr message)
                              { bot.getApi().sendMessage(message->chat->id, "you used comand print"); });

    bot.getEvents().onNonCommandMessage([&bot](TgBot::Message::Ptr message)
                                        {
                                    std::reverse(message->text.begin(), message->text.end());
                                    bot.getApi().sendMessage(message->chat->id, message->text); });
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