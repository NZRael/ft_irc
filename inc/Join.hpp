#pragma once

#include "ACommand.hpp"

class Join : public ACommand {
    public:
        Join();
        ~Join();
        void execute(/*a determiner*/);
};