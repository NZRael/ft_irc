#include "../inc/User.hpp"

User::User() : ACommand("USER") {
}

User::~User() {
}

void User::execute(Client *user, std::string raw_message, Server *server) const{
	(void)server;
	std::istringstream iss(raw_message);
    std::string username, hostname, servername, realname;
    
    if (!(iss >> username >> hostname >> servername)) {
        user->sendMessage(":server 461 " + user->getNickname() + " USER :Not enough parameters\r\n");
        return;
    }

    std::getline(iss, realname);
    realname.erase(0, realname.find_first_not_of(" "));
    if (realname.empty() || realname[0] != ':') {
        std::cout << "realname: " << realname << std::endl;
        user->sendMessage(":server 461 " + user->getNickname() + " USER :Not enough parameters\r\n");
        return;
    }
    realname = realname.substr(1);
	if (realname.find(' ') == std::string::npos) {
		user->sendMessage(":server 461 " + user->getNickname() + " USER :Not enough parameters\r\n");
		return;
	}

    if (!user->isUserAuthenticated()) {
        user->sendMessage(":server 462 " + user->getNickname() + " USER :Unauthorized command (already registered)\r\n");
        return;
    }

    if (!isValidUsername(username)) {
        user->sendMessage("Invalid username\r\n");
        return;
    }

    user->setUsername(username);
    user->setRealname(realname);

    if (!user->getNickname().empty()) {
        user->setAuthenticated(true);
        user->sendMessage(":server 001 " + user->getNickname() + " :Welcome to the Internet Relay Network " + user->getPrefix() + "\r\n");
        user->sendMessage(":server 002 " + user->getNickname() + " :Your host is server, running version 1.0\r\n");
        user->sendMessage(":server 003 " + user->getNickname() + " :This server was created testSeptembertest25, 2024\r\n");
        user->sendMessage(":server 004 " + user->getNickname() + " server 1.0 * *\r\n");
        user->setPrefix();
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