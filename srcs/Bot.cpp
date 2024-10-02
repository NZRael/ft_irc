#include "../inc/Bot.hpp"

Bot::Bot() : ACommand("BOT") {}

Bot::~Bot() {}

void Bot::start(Client *user) const {

    user->sendMessage("Bonjour");
} 

void Bot::nbr_game(Client *user){
    start(user);
}


void Bot::execute(Client *user, std::string raw_message, Server *server) const{
	if (raw_message.empty())
	    return;
	(void)server;
    if (raw_message == "bonjour")
        start(user);
}