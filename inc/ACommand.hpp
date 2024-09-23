#pragma once

#include "ft_irc.hpp"

class ACommand {
public:
	ACommand(std::string name);
	virtual ~ACommand();

	std::string getName() const;
	virtual void execute(Client *user, std::string raw_message, Server *server) const = 0;
protected:
	std::string _name;
	bool _isValid;
};
