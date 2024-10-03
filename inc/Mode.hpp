#pragma once

#include "ft_irc.hpp"

class Mode : public ACommand {
    public:
        Mode();
        ~Mode();
        void execute(Client *user, std::string raw_message, Server *server) const;
};
