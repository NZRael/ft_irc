#include "../inc/Mode.hpp"

Mode::Mode() : ACommand("MODE") {
}

Mode::~Mode() {
}

void Mode::execute(Client *user, std::string raw_message, Server *server) const{
	std::istringstream iss(raw_message);
	std::string channelMode, modeString, modeParam;

	if (raw_message == user->getNickname() + " +i")
		return ;
	iss >> channelMode;
	if (channelMode.empty())
	{
		user->sendMessage(":server 461 " + user->getNickname() + " MODE :not enough parameters\r\n");
		return;
	}
	else {
		if (channelMode[0] != '#')
		{
			user->sendMessage(":server 403 " + user->getNickname() + " " + channelMode + " :No such a channel\r\n");
			return;
		}
	}
	Channel *channel = server->getChannelByName(channelMode);
	if (!channel)
	{
		user->sendMessage(":server 403 " + user->getNickname() + " " + channelMode + " :No such a channel\r\n");
		return;
	}

	if (!(iss >> modeString))
	{
		std::string activeModes = "+";
		if (channel->isInviteOnly()) 
			activeModes += "i";
		activeModes += "n";
		if (channel->isTopicRestricted())
			activeModes +="t";
        if (channel->getUserLimit() > 0) 
			activeModes += "l";
		if (!channel->checkPassword("")) 
			activeModes += "k";
		if (channel->getUserLimit() > 0) 
			activeModes += " " + intToString(channel->getUserLimit());
		if (!channel->checkPassword("")) 
			activeModes += " " + channel->getPassword();
		user->sendMessage(":server 324 " + user->getNickname() + " " + channel->getName() + " " + activeModes);

		std::ostringstream oss;
		oss << channel->getCreationTime();
		std::string message = ":server 329 " + user->getNickname() + " " + channel->getName() + " " + oss.str();
		user->sendMessage(message);
		return;
	}

	if(!channel->isOperator(user))
	{
		user->sendMessage(":server 441 " + user->getNickname() + " " + channelMode + " :You're not channel operator\r\n");
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