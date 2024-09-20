#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "ACommand.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <map>
#include <sstream>
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

    std::string getPassword() const;
    int getPort() const;
    int getServerSocket() const;
    void initCommand();

private:
    void setupSocket();
    void handleNewConnection(std::vector<pollfd>& fds);
    void handleClientMessage(std::vector<pollfd>& fds, size_t index);
    void parseMessage(int index_user, const std::string& raw_message);

    int port;
    std::string password;
    int serverSocket;
    std::vector<Client *> users;

    std::vector<ACommand *> command; // initialise les classes de commandes
};

#endif