#include "../inc/Topic.hpp"

Topic::Topic() : ACommand("TOPIC") {
}

Topic::~Topic() {
}

void Topic::execute(Client *user, std::string raw_message, Server *server) const{
	std::istringstream iss(raw_message);
    std::string channelName, newTopic;

	if (!(iss >> channelName)) {
		user->sendMessage(":server 461 " + user->getNickname() + " TOPIC :Not enough parameters");
		return ;
	}

	Channel *channel = server->getChannelByName(channelName);
	if (!channel)
	{
		user->sendMessage(":server 403 " + user->getNickname() + " " + channelName + " :No such channel");
		return ;
	}

	if (!channel->hasUser(user))
	{
		user->sendMessage(":server 442 " + user->getNickname() + " " + channelName + " : You're not on that channel");
	}
	std::getline(iss, newTopic);
	if (newTopic.empty()) {
        // View topic
        if (channel->getTopic().empty()) {
            user->sendMessage(":server 331 " + user->getNickname() + " " + channelName + " :No topic is set");
        } else {
            user->sendMessage(":server 332 " + user->getNickname() + " " + channelName + " :" + channel->getTopic());
        }
    } else {
        // Set topic
        if (channel->isTopicRestricted() && !channel->isOperator(user)) {
            user->sendMessage(":server 482 " + user->getNickname() + " " + channelName + " :You're not channel operator");
            return;
        }
        
        newTopic = newTopic.substr(1); // Remove leading space
        channel->setTopic(newTopic);
        channel->broadcastMessage(":" + user->getNickname() + " TOPIC " + channelName + " :" + newTopic);
    }
}