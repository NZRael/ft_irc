#pragma once

#include "ACommand.hpp"

class Join : public ACommand {
    public:
        Join();
        ~Join();
        void execute(Client *user, std::string raw_message);
};