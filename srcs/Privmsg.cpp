#include "../inc/Privmsg.hpp"

Privmsg::Privmsg() : ACommand("PRIVMSG") {
}

Privmsg::~Privmsg() {
}

void Privmsg::execute(Client* user, std::string raw_message, Server *server) const {
    std::istringstream iss(raw_message);
    std::string target, msgContent;
    
    if (!(iss >> target)) {
        user->sendMessage(":server 411 " + user->getNickname() + " :No recipient given (PRIVMSG)\r\n");
        return;
    }

    std::getline(iss, msgContent);
    msgContent.erase(0, msgContent.find_first_not_of(" "));
    if (msgContent.empty() || msgContent[0] != ':') {
        user->sendMessage(":server 412 " + user->getNickname() + " :No text to send\r\n");
        return;
    }
    msgContent = msgContent.substr(1);
    if (target[0] == '#' || target[0] == '&') {

        Channel* channel = server->getChannelByName(target);
        if (!channel) {
            user->sendMessage(":server 403 " + user->getNickname() + " " + target + " :No such channel\r\n");
            return;
        }

        if (!channel->hasUser(user)) {
            user->sendMessage(":server 404 " + user->getNickname() + " " + target + " :Cannot send to channel\r\n");
            return;
        }
        std::string fullMessage = ":" + user->getNickname() + " PRIVMSG " + target + " :" + msgContent;
        channel->broadcastMessage(fullMessage, user); // on envoie l'user pour pas avoir a afficher le message qu'il vient d'envoyer dans son client
    } else {
        // Private message to a user
        Client* targetClient = server->getClientByNick(target);
        if (!targetClient) {
            user->sendMessage(":server 401 " + user->getNickname() + " " + target + " :No such nick/channel\r\n");
            return;
        }

        std::string fullMessage = ":" + user->getNickname() + " PRIVMSG " + target + " :" + msgContent + "\r\n";
        targetClient->sendMessage(fullMessage);
    }
}
