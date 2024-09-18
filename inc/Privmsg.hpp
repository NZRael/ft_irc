#pragma once

#include "ACommand.hpp"

class Privmsg : public ACommand {
    public:
        Privmsg();
        ~Privmsg();
        void execute(/*a determiner*/);
};