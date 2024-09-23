#include "../inc/Topic.hpp"

Topic::Topic() : ACommand("TOPIC") {
}

Topic::~Topic() {
}

void Topic::execute(Client *user, std::string raw_message, Server *server) const{
}