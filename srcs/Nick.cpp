#include "../inc/Nick.hpp"

Nick::Nick() : ACommand("NICK") {
}

Nick::~Nick() {
}

bool Nick::isValidNickname(const std::string& nick) const {
    if (nick.length() > 9)
        return false;
	const std::string validFirstChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz[]\\`_^{|}";
    const std::string validChars = validFirstChar + "0123456789-";
    if (validFirstChar.find(nick[0]) == std::string::npos)
        return false;
    for (std::string::const_iterator it = nick.begin(); it != nick.end(); ++it) {
        if (validChars.find(*it) == std::string::npos)
            return false;
    }
    return true;
}

void Nick::execute(Client *user, std::string raw_message, Server *server) const{
	if (raw_message.empty()) {
		user->sendMessage(":server 431 * :Expected nickname and have none");
		return;
	}
	if (!isValidNickname(raw_message)) {
        user->sendMessage(":server 432 * " + raw_message + " :Erroneous nickname");
        return;
    }
	if (server->isNicknameUsed(raw_message)) {
        user->sendMessage(":server 433 * " + raw_message + " :Nickname is already in use");
        return;
    }
	if (user->getNickname().empty()) {
		user->setNickname(raw_message);
		user->sendMessage(":" + user->getNickname() + " NICK " + user->getNickname());
	}
	else {
		std::string oldNick = user->getNickname();
		user->setNickname(raw_message);
		user->sendMessage(":" + oldNick + " NICK " + user->getNickname());
	}
}
