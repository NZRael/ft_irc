#pragma once

#include "ACommand.hpp"

class Mode : public ACommand {
    public:
        Mode();
        ~Mode();
        void execute(Client *user, std::string raw_message);
};