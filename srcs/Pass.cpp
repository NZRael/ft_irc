#include "../inc/Pass.hpp"

Pass::Pass() : ACommand("PASS") {}

Pass::~Pass() {}

void Pass::execute(Client *user, std::string raw_message, Server *server) const {
    if (user->getPassword()) {
        user->sendMessage(":server 462 " + user->getNickname() + " :You may not reregister");
        return;
    }
    if (raw_message.empty()) {
        user->sendMessage(":server 461 " + user->getNickname() + " PASS :Not enough parameters");
        return;
    }
    // std::istringstream iss(raw_message);
    // std::string password;
    // iss >> password;
    user->setPassword(true);
}
