#include "../inc/Nick.hpp"

Nick::Nick() : ACommand("NICK") {
}

Nick::~Nick() {
}

void Nick::execute(Client *user, std::string raw_message, Server *server) const{
	if (raw_message.empty()) {
		user->sendMessage(":server 431 NICK :Expected nickname and have none");
		return;
	}

}