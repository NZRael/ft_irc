#include "../inc/Join.hpp"

Join::Join() : ACommand("JOIN") {
}

Join::~Join() {
}

void Join::execute(Client *user, std::string raw_message, Server *server) const{
	std::istringstream iss(raw_message);
	std::string channelName, key;
	bool	newChannel = false;
	
	if (!(iss >> channelName)) {
		user->sendMessage(":server 461 " + user->getNickname() + " JOIN :Not enough parameters\r\n");
		return;
	}

	iss >> key; // Key is optional

	Channel* channel = server->getChannelByName(channelName);
	if (!channel) {
		channel = new Channel(channelName);
		server->addChannel(channel);
		newChannel = true;
	}

	if (channel->isInviteOnly() && !channel->isInvited(user)) {
		user->sendMessage(":server 473 " + user->getNickname() + " " + channelName + " :Cannot join channel (+i)\r\n");
		return;
	}

	if (!channel->checkPassword(key)) {
		user->sendMessage(":server 475 " + user->getNickname() + " " + channelName + " :Cannot join channel (+k)\r\n");
		return;
	}

	if (channel->getUserLimit() > 0 && channel->getUsers().size() >= channel->getUserLimit()) {
		user->sendMessage(":server 471 " + user->getNickname() + " " + channelName + " :Cannot join channel (+l)\r\n");
		return;
	}

	channel->addUser(user);
	user->joinChannel(channel);
	if (newChannel == true)
		channel->addOperator(user);

	std::string joinMessage = ":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " JOIN " + channelName + "\r\n";
	channel->broadcastMessage(joinMessage);

	if (!channel->getTopic().empty()) {
		user->sendMessage(":server 332 " + user->getNickname() + " " + channelName + " :" + channel->getTopic() + "\r\n");
	}

	std::string userList = ":server 353 " + user->getNickname() + " = " + channelName + " :";
	const std::vector<Client*>& users = channel->getUsers();
	for (std::vector<Client*>::const_iterator it = users.begin(); it != users.end(); ++it) {
		if (channel->isOperator(*it)) {
			userList += "@";
		}
		userList += (*it)->getNickname() + " ";
	}
	user->sendMessage(userList);
	user->sendMessage(":server 366 " + user->getNickname() + " " + channelName + " :End of /NAMES list.\r\n");
	
}