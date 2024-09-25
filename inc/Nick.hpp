#pragma once

#include "ft_irc.hpp"

class Nick : public ACommand {
    public:
        Nick();
        ~Nick();
        bool isValidNickname(const std::string& nick) const;
        void execute(Client *user, std::string raw_message, Server *server) const;
};