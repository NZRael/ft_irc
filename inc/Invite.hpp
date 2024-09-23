#pragma once

#include "ft_irc.hpp"

class Client;
class ACommand;

class Invite : public ACommand {
    public:
        Invite();
        ~Invite();
        void execute(Client *user, std::string raw_message, Server *server) const;
};
