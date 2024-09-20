#pragma once

#include "ft_irc.hpp"

class Topic : public ACommand {
    public:
        Topic();
        ~Topic();
        void execute(Client *user, std::string raw_message) const;
};