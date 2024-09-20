#pragma once

#include "ACommand.hpp"

class Pass : public ACommand {
    public:
        Pass();
        ~Pass();
        void execute(Client* client, const std::string& message);
};