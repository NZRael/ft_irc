#include "../inc/Mode.hpp"

Mode::Mode() : ACommand("MODE") {
}

Mode::~Mode() {
}

void Mode::execute(Client *user, std::string raw_message, Server *server) const{
	std::istringstream iss(raw_message);
	std::string channelMode, modeString, modeParam;

	if (!(iss >> channelMode >> modeString))
	{
		user->sendMessage(":server 461 " + user->getNickname() + " MODE :not enough parameters\r\n");
		return;
	}
	Channel *channel = server->getChannelByName(channelMode);
	if (!channel)
	{
		user->sendMessage(":server 403 " + user->getNickname() + " " + channelMode + " :No such a channel\r\n");
		return;
	}

	if(!channel->isOperator(user))
	{
		user->sendMessage(":server " + user->getNickname() + " " + channelMode + " :You're not channel operator\r\n");
		return ;
	}

	bool adding = true;
    for (std::string::const_iterator it = modeString.begin(); it != modeString.end(); ++it) {
        char mode = *it;
        if (mode == '+') {
            adding = true;
        } else if (mode == '-') {
            adding = false;
        } else {
            iss >> modeParam;
            channel->setMode(mode, adding, user, modeParam, server);
        }
    }
}