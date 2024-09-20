#pragma once

#include "ft_irc.hpp"

class Client;

class Join : public ACommand {
    public:
        Join();
        ~Join();

        void execute(Client *user, std::string raw_message) const;
};
