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
		reason.erase(0, reason.find_first_not_of(" "));
        reason = reason.substr(1);
    }

	Channel *channel = server->getChannelByName(channelName);
	if (!channel)
	{
		user->sendMessage(":server 403 " + user->getNickname() + " " + channelName + " :No such a channel");
		return ;
	}

	if (!channel->hasUser(user))
	{
		user->sendMessage(":server 442 " + user->getNickname() + " " + channelName + " :You're not on that channel");
		return ;
	}

	if (!channel->isOperator(user))
	{
		user->sendMessage(":server 482 " + user->getNickname() + " " + channelName + " :You're not a channel operator");
		return ;
	}
	Client *target = server->getClientByNick(targetKick);
	if (!target || !channel->hasUser(target))
	{
		user->sendMessage(":server 441 " + user->getNickname() + " " + target->getNickname() + " " + channelName + " :They aren't on that channel");
		return;
	}
	if (target->getNickname() == user->getNickname())
	{
		user->sendMessage(":server " + user->getNickname() + " :You can't kick yourself");
		return ;
	}
	channel->broadcastMessage(user->getPrefix() + " KICK " + channelName + " " + targetKick);
	channel->removeUser(target);
}
