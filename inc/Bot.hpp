#pragma once

#include "ft_irc.hpp"

class Bot : public ACommand {
    public:
        Bot();
        ~Bot();
        void start(Client *user) const;

        void nbr_game(Client *user);
        void execute(Client *user, std::string raw_message, Server *server) const;

    private:
        int guess_nbr;
};