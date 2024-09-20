#pragma once

#include "ft_irc.hpp"

class User : public ACommand {
    public:
        User();
        ~User();
        void execute(Client *user, std::string raw_message) const;
};