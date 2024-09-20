#include "../inc/Invite.hpp"

Invite::Invite() : ACommand("INVITE") {
}

Invite::~Invite() {
}

void Invite::execute(Client *user, std::string raw_message) const{
}
