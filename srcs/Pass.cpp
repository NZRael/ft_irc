#include "Pass.hpp"

Pass::Pass() : ACommand("PASS") {}

Pass::~Pass() {}

void Pass::execute(Client* client, const std::string& message) {
    // Implement the PASS command logic here
}