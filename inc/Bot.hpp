#pragma once

#include "ft_irc.hpp"

#define BONJOUR "Bonjour"
#define SAL "Salut"

class Bot : public ACommand {
    public:
        Bot();
        ~Bot();
        void start(Client *user) const;
        void execute(Client *user, std::string raw_message, Server *server) const;
};