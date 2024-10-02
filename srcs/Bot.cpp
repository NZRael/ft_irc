#include "../inc/Bot.hpp"

Bot::Bot() : ACommand("BOT") {}

Bot::~Bot() {}

void Bot::start(Client *user) const {
    user->sendMessage(":BOT Bonjour " + user->getNickname() + " !");
}


void Bot::execute(Client *user, std::string raw_message, Server *server) const{
	if (raw_message.empty())
	    return;
	(void)server;
    if (raw_message == BONJOUR || raw_message == SAL)
        start(user);
	else
		user->sendMessage(":BOT Je ne comprends pas ce que vous voulez dire.");
}