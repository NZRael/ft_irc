#include "../inc/Pass.hpp"

Pass::Pass() : ACommand("PASS") {}

Pass::~Pass() {}

void Pass::execute(Client *user, std::string raw_message, Server *server) const {
    std::istringstream iss(raw_message);
}