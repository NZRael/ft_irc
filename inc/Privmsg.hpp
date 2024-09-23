#pragma once

#include "ft_irc.hpp"

class Privmsg : public ACommand {
    public:
        Privmsg();
        ~Privmsg();
        void execute(Client *user, std::string raw_message, Server *server) const;
};