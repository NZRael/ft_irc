#pragma once

#include "ACommand.hpp"

class Topic : public ACommand {
    public:
        Topic();
        ~Topic();
        void execute(Client *user, std::string raw_message);
};