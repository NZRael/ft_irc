#pragma once

#include "ACommand.hpp"

class Invite : public ACommand {
    public:
        Invite();
        ~Invite();
        void execute(Client *user, std::string raw_message);
};