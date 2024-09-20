#pragma once

#include "ft_irc.hpp"

class Pass : public ACommand {
    public:
        Pass();
        ~Pass();
        void execute(Client *user, std::string raw_message) const;
};