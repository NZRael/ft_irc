#include "../inc/User.hpp"

User::User() : ACommand("USER") {
}

User::~User() {
}

void User::execute(Client *user, std::string raw_message, Server *server) const{
}