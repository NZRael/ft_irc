#pragma once

#include "ACommand.hpp"

class Topic : public ACommand {
    public:
        Topic();
        ~Topic();
        void execute(/*a determiner*/);
};