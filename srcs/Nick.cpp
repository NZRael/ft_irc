#include "../inc/Nick.hpp"

Nick::Nick() : ACommand("NICK") {
}

Nick::~Nick() {
}

void Nick::execute(Client *user, std::string raw_message) {
}