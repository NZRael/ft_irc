#include "../inc/Kick.hpp"

Kick::Kick() : ACommand("KICK") {
}

Kick::~Kick() {
}

void Kick::execute(Client *user, std::string raw_message, Server *server) const{
}