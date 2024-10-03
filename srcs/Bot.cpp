#include "../inc/Bot.hpp"

Bot::Bot() : ACommand("BOT") {}

Bot::~Bot() {}

void Bot::start(Client *user) const {
    user->sendMessage("Bonjour " + user->getNickname() + "!");
    user->sendMessage("Je suis un bot, je peux vous donner l'heure si vous me le demandez.");
    user->sendMessage("Essayez de taper 'time' pour voir l'heure.");
}

void Bot::give_time(Client *user) const{
    time_t rawtime = time(0);
    std::string time = ctime(&rawtime);
    user->sendMessage("Time is : " + time);
}

void Bot::execute(Client *user, std::string raw_message, Server *server) const{
	if (raw_message.empty())
	    return;
	(void)server;
    if (raw_message == "bonjour" || raw_message == "Bonjour")
        start(user);
    else if (raw_message == "salut" || raw_message == "Salut"){
        user->sendMessage("Salut " + user->getNickname() + "!");
        user->sendMessage("Je suis un bot, je peux vous donner l'heure si vous me le demandez.");
        user->sendMessage("Essayez de taper 'time' pour voir l'heure.");
    }
    else if (raw_message == "time")
        give_time(user);
    else {
        user->sendMessage("Je ne comprends pas ce que vous voulez dire.");
        user->sendMessage("Essayez de taper 'time' , 'Bonjour' ou 'Salut'.");
    }
}
