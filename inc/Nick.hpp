#pragma once

#include "ft_irc.hpp"

class Nick : public ACommand {
    public:
        Nick();
        ~Nick();
        void execute(Client *user, std::string raw_message, Server *server) const;
};