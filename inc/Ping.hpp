#pragma once

#include "ft_irc.hpp"

class Ping : public ACommand {
	public:
		Ping();
		~Ping();
		void execute(Client *user, std::string raw_message, Server *server) const;
};
