#include "../inc/ACommand.hpp"

ACommand::ACommand(std::string name) : _name(name){}

ACommand::~ACommand() {}

std::string ACommand::getName() const {
    return _name;
}
