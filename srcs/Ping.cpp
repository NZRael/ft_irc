#include "../inc/Ping.hpp"

Ping::Ping() : ACommand("PING") {}

Ping::~Ping() {}

void Ping::execute(Client *user, std::string raw_message, Server *server) const {
	if (raw_message.empty()) {
		user->sendMessage(":server 461 " + user->getNickname() + " PING :Not enough parameters\r\n");
		return;
	}
	(void)server;
	user->sendMessage("PONG\r\n");
}
