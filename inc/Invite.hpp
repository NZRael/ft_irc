#pragma once

#include "ACommand.hpp"

class Invite : public ACommand {
    public:
        Invite();
        ~Invite();
        void execute(/*a determiner*/);
};