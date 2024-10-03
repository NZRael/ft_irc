#include "../inc/Invite.hpp"

Invite::Invite() : ACommand("INVITE") {
}

Invite::~Invite() {
}

void Invite::execute(Client* user, std::string raw_message, Server *server) const {
    std::istringstream iss(raw_message);
    std::string nickname, channelName;
    
    if (!(iss >> nickname >> channelName)) {
        user->sendMessage(":server 461 " + user->getNickname() + " INVITE :Not enough parameters");
        return;
    }

    Channel* channel = server->getChannelByName(channelName);
    if (!channel) {
        user->sendMessage(":server 403 " + user->getNickname() + " " + channelName + " :No such channel");
        return;
    }

    if (!channel->hasUser(user)) {
        user->sendMessage(":server 442 " + user->getNickname() + " " + channelName + " :You're not on that channel");
        return;
    }

    if (channel->isInviteOnly() && !channel->isOperator(user)) {
        user->sendMessage(":server 482 " + user->getNickname() + " " + channelName + " :You're not channel operator");
        return;
    }

    Client* target = server->getClientByNick(nickname);
    if (!target) {
        user->sendMessage(":server 401 " + user->getNickname() + " " + nickname + " :No such nick/channel");
        return;
    }

    if (channel->hasUser(target)) {
        user->sendMessage(":server 443 " + user->getNickname() + " " + nickname + " " + channelName + " :is already on channel");
        return;
    }

    channel->addUser(target);
    channel->inviteUser(target);
    target->sendMessage(":" + user->getNickname() + " INVITE " + nickname + " :" + channelName);
    user->sendMessage(":server 341 " + user->getNickname() + " " + nickname + " " + channelName);
}
