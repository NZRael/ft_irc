#include "../inc/Pass.hpp"

Pass::Pass() : ACommand("PASS") {}

Pass::~Pass() {}

void Pass::execute(Client *user, std::string raw_message, Server *server) const {
    if (user->isUserAuthenticated()) {
        user->sendMessage(":server 462 " + user->getNickname() + " :You are already register\r\n");
        return;
    }
    if (raw_message.empty()) {
        user->sendMessage(":server 461 " + user->getNickname() + " PASS :Not enough parameters\r\n");
        return;
    }
    std::istringstream iss(raw_message);
    std::string password;
    iss >> password;
    if (password != server->getPassword()) {
        user->sendMessage(":server 464 " + user->getNickname() + " :Password incorrect\r\n");
        return;
    }
    else
        user->setAuthenticated(true);
}
