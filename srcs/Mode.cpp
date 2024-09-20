#include "../inc/Mode.hpp"

Mode::Mode() : ACommand("MODE") {
}

Mode::~Mode() {
}

void Mode::execute(Client *user, std::string raw_message) const{}