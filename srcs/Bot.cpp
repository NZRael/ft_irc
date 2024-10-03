#include "../inc/Bot.hpp"

Bot::Bot() : ACommand("BOT") {}

Bot::~Bot() {}

void Bot::start(Client *user) const {

    user->sendMessage("Bonjour");
} 

void Bot::give_time(Client *user) const{

    time_t rawtime = time(0);
    std::string time = ctime(&rawtime);
    user->sendMessage("Time : " + time);

}


void Bot::execute(Client *user, std::string raw_message, Server *server) const{
	if (raw_message.empty())
	    return;
	(void)server;
    if (raw_message == "bonjour")
        start(user);
    if (raw_message == "time")
        give_time(user);
}