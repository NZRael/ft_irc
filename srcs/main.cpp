#include <iostream>
#include <string>
#include "Command.hpp"

void testParsing(const std::string& raw_message) {
    std::cout << "Message brut : " << raw_message << std::endl;
    
    Command cmd(raw_message);
    
    std::cout << "Préfixe : " << cmd.getPrefix() << std::endl;
    std::cout << "Commande : " << cmd.getName() << std::endl;
    
    std::cout << "Paramètres : ";
    std::vector<std::string> params = cmd.getParams();
    for (std::vector<std::string>::const_iterator it = params.begin(); it != params.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Message trailing : " << cmd.getTrailing() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

int main() {
    // Test 1 : Message complet avec préfixe, commande, paramètres et trailing
    testParsing(":prefix PRIVMSG #channel param1 param2 :Ceci est un message trailing");

    // Test 2 : Message sans préfixe
    testParsing("JOIN #channel");

    // Test 3 : Message avec seulement une commande
    testParsing("PING");

    // Test 4 : Message avec préfixe et commande, sans paramètres ni trailing
    testParsing(":server PONG");

    // Test 5 : Message avec caractères spéciaux et espaces dans le trailing
    testParsing("PRIVMSG #channel :Bonjour, comment allez-vous ? :)");

    // Test 6 : Message avec plusieurs espaces entre les éléments
    testParsing(":nick!user@host   PRIVMSG   #channel   :  Message avec des espaces  ");

    return 0;
}
