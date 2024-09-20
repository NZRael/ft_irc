#pragma once

#include "ft_irc.hpp"

class Kick : public ACommand {
    public:
        Kick();
        ~Kick();
        void execute(Client *user, std::string raw_message) const;
};