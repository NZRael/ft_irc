#ifndef SERVER_HPP
#define SERVER_HPP

#include "ACommand.hpp"

#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <map>
#include <sstream>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <map>
#include <arpa/inet.h>


class Server {
public:
    Server(int port, const std::string& password);
    ~Server();
    void run();
    void stop();

    void initCommand();

private:
    void setupSocket();
    void handleNewConnection(std::vector<pollfd>& fds);
    void handleClientMessage(std::vector<pollfd>& fds, size_t index);
    bool parseMessage(const std::string& raw_message);

    int port;
    std::string password;
    int serverSocket;
    std::vector<int> clientSockets;
    std::map<int, std::string> clientMap; // Associe chaque socket à un identifiant client
    std::vector<ACommand *> command; // initialise les classes de commandes
};

#endif