#include "../inc/Kick.hpp"

Kick::Kick() : ACommand("KICK") {
}

Kick::~Kick() {
}

void Kick::execute(Client *user, std::string raw_message, Server *server) const{
	std::istringstream iss(raw_message);
	std::string channelName, targetKick, reason;

	if (!(iss >> channelName >> targetKick))
	{
		user->sendMessage(":server 461 " + user->getNickname() + " KICK : Not enough parameters");
		return ;
	}

	std::getline(iss, reason);
	if (reason.empty()) {
        reason = user->getNickname();
    } else {
        reason = reason.substr(1); // Remove leading space
    }

	Channel *channel = server->getChannelByName(channelName);
	if (!channel)
	{
		user->sendMessage(":server 403 " + user->getNickname() + " " + channelName + " :No such a channel");
		return ;
	}

	if (!channel->isOperator(user))
	{
		user->sendMessage(":server 482 " + user->getNickname() + " " + channelName + " :You are not channel operator");
		return ;
	}
	Client *target = server->getClientByNick(targetKick);
	if (!target || !channel->hasUser(target))
	{
		user->sendMessage(":server 441 " + user->getNickname() + " " + targetKick + " " + channelName + " :They aren't on the channel ");
		return;
	}

	channel->broadcastMessage(":" + user->getNickname() + " KICK " + targetKick + " from : " + channelName);
	channel->removeUser(target);
}