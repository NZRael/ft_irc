#include "Command.hpp"
#include <sstream>

Command::Command() {}

Command::Command(const std::string& raw_message) {
    parse(raw_message);
}

Command::~Command() {}

void Command::parse(const std::string& raw_message) {
    std::string message = raw_message;

    // Supprimer les caractères CR et LF à la fin
    std::string::iterator end = message.end();
    while (end != message.begin() && (*(end - 1) == '\r' || *(end - 1) == '\n')) {
        --end;
    }
    message.erase(end, message.end());

    std::istringstream iss(message);
    std::string token;

    // Vérifier le préfixe
    if (!message.empty() && message[0] == ':') {
        iss >> prefix;
        prefix = prefix.substr(1); // Enlever le ':' initial
    }

    // Lire la commande
    iss >> name;

    // Lire les paramètres et le trailing
    std::string param;
    while (iss >> param) {
        if (param[0] == ':') {
            trailing = message.substr(message.find(param) + 1);
            break;
        }
        params.push_back(param);
    }
}

std::string Command::getPrefix() const {
    return prefix;
}

std::string Command::getName() const {
    return name;
}

std::vector<std::string> Command::getParams() const {
    return params;
}

std::string Command::getTrailing() const {
    return trailing;
}
