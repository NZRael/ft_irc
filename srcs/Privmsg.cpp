#include "../inc/Privmsg.hpp"

Privmsg::Privmsg() : ACommand("PRIVMSG") {
}

Privmsg::~Privmsg() {
}

void Privmsg::execute(Client *user, std::string raw_message) const{
}
