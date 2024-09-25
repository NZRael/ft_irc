#include "../inc/Invite.hpp"

Invite::Invite() : ACommand("INVITE") {
}

Invite::~Invite() {
}

void Invite::execute(Client* user, std::string raw_message, Server *server) const {
    std::istringstream iss(raw_message);
    std::string nickname, channelName;
    
    if (!(iss >> nickname >> channelName)) {
        user->sendMessage(":server 461 " + user->getNickname() + " INVITE :Not enough parameters\r\n");
        return;
    }

    Channel* channel = server->getChannelByName(channelName);
    if (!channel) {
        user->sendMessage(":server 403 " + user->getNickname() + " " + channelName + " :No such channel\r\n");
        return;
    }

    if (!channel->hasUser(user)) {
        user->sendMessage(":server 442 " + user->getNickname() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }

    if (channel->isInviteOnly() && !channel->isOperator(user)) {
        user->sendMessage(":server 482 " + user->getNickname() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }

    Client* target = server->getClientByNick(nickname);
    if (!target) {
        user->sendMessage(":server 401 " + user->getNickname() + " " + nickname + " :No such nick/channel\r\n");
        return;
    }

    if (channel->hasUser(target)) {
        user->sendMessage(":server 443 " + user->getNickname() + " " + nickname + " " + channelName + " :is already on channel\r\n");
        return;
    }

    channel->addUser(target);
    target->sendMessage(":" + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + " INVITE " + nickname + " :" + channelName);
    user->sendMessage(":server 341 " + user->getNickname() + " " + nickname + " " + channelName + "\r\n");
}