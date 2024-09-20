#pragma once

#include "ACommand.hpp"

class User : public ACommand {
    public:
        User();
        ~User();
        void execute(Client *user, std::string raw_message);
};