#pragma once

#include "ft_irc.hpp"

class User : public ACommand {
    public:
        User();
        ~User();
        bool    isValidUsername(const std::string& username) const;
        void execute(Client *user, std::string raw_message, Server *server) const;
};