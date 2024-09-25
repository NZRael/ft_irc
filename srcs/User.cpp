#include "../inc/User.hpp"

User::User() : ACommand("USER") {
}

User::~User() {
}

void User::execute(Client *user, std::string raw_message, Server *server) const{
	std::istringstream iss(raw_message);
    std::string username, hostname, servername, realname;
    
    if (!(iss >> username >> hostname >> servername)) {
        user->sendMessage(":server 461 " + user->getNickname() + " USER :Not enough parameters");
        return;
    }

    // Get the real name (which may contain spaces)
    std::getline(iss, realname);
    if (realname.empty() || realname[0] != ':') {
        user->sendMessage(":server 461 " + user->getNickname() + " USER :Not enough parameters");
        return;
    }
    realname = realname.substr(1); // Remove the leading ':'

    if (user->isUserAuthenticated()) {
        user->sendMessage(":server 462 " + user->getNickname() + " :You may not reregister");
        return;
    }

    if (!isValidUsername(username)) {
        user->sendMessage(":server 468 " + user->getNickname() + " :Invalid username");
        return;
    }

    user->setUsername(username);
    user->setHostname(hostname);
    user->setRealname(realname);

    // Check if both NICK and USER have been received
    if (!user->getNickname().empty()) {
        user->setAuthenticated(true);
        // Send welcome messages
        user->sendMessage(":server 001 " + user->getNickname() + " :Welcome to the Internet Relay Network " + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname());
        user->sendMessage(":server 002 " + user->getNickname() + " :Your host is server, running version 1.0");
        user->sendMessage(":server 003 " + user->getNickname() + " :This server was created September 25, 2024");
        user->sendMessage(":server 004 " + user->getNickname() + " server 1.0 o o");
    }
}

bool User::isValidUsername(const std::string& username) const {
    if (username.empty() || username.length() > 9) {
        return false;
    }

    // Check if username contains only allowed characters
    return std::find_if(username.begin(), username.end(), 
                        std::not1(std::ptr_fun(static_cast<int(*)(int)>(std::isalnum)))) == username.end();
}