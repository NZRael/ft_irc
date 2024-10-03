#pragma once

#include "ft_irc.hpp"

class Bot : public ACommand {
    public:
        Bot();
        ~Bot();
        void start(Client *user) const;

        void give_time(Client *user) const;
        void execute(Client *user, std::string raw_message, Server *server) const;

    private:
        int guess_nbr;
};