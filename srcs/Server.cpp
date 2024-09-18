#include "Server.hpp"


Server::Server(int port, const std::string& password) : port(port), password(password), serverSocket(-1) {
    std::cout << "Serveur créé sur le port " << port << std::endl;
}

Server::~Server() {
    stop();
}

void Server::run() {
    setupSocket();
    std::cout << "Serveur en écoute sur le port " << port << std::endl;

    std::vector<pollfd> fds;
    pollfd serverPollFd;
    serverPollFd.fd = serverSocket;
    serverPollFd.events = POLLIN;
    fds.push_back(serverPollFd);

    while (true) {
        int ret = poll(&fds[0], fds.size(), -1);
        if (ret < 0) {
            throw std::runtime_error("Erreur lors de l'appel à poll()");
        }

        for (size_t i = 0; i < fds.size(); ++i) {
            if (fds[i].revents & POLLIN) {
                if (fds[i].fd == serverSocket) {
                    handleNewConnection(fds);
                } else {
                    handleClientMessage(fds, i);
                }
            }
        }
    }
}

void Server::setupSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw std::runtime_error("Erreur lors de la création du socket");
    }

    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        throw std::runtime_error("Erreur lors de la configuration du socket");
    }

    struct sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Erreur lors de la liaison du socket");
    }

    if (listen(serverSocket, 5) < 0) {
        throw std::runtime_error("Erreur lors de la mise en écoute du socket");
    }
}

void Server::handleNewConnection(std::vector<pollfd>& fds) {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
        std::cerr << "Erreur lors de l'acceptation d'une nouvelle connexion" << std::endl;
    } else {
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
        std::string clientId = std::string(clientIP) + ":" + std::to_string(ntohs(clientAddr.sin_port));
        
        std::cout << "Nouvelle connexion acceptée de " << clientId << std::endl;
        
        pollfd clientPollFd;
        clientPollFd.fd = clientSocket;
        clientPollFd.events = POLLIN;
        fds.push_back(clientPollFd);
        clientSockets.push_back(clientSocket);
        clientMap[clientSocket] = clientId;
    }
}

void Server::handleClientMessage(std::vector<pollfd>& fds, size_t index) {
    char buffer[1024];
    int clientSocket = fds[index].fd;
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        std::cout << "Connexion fermée pour le client " << clientMap[clientSocket] << std::endl;
        close(clientSocket);
        fds.erase(fds.begin() + index);
        std::vector<int>::iterator it = std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
        if (it != clientSockets.end()) {
            clientSockets.erase(it);
        }
        clientMap.erase(clientSocket);
    } else {
        buffer[bytesRead] = '\0';
        std::cout << "Reçu de " << clientMap[clientSocket] << " : " << buffer << std::endl;
        parseMessage(buffer);
    }
}

// fonction void qui va instancier la class ACommand avec toutes les commandes ex: this->command.push_back(new JoinCommand());
void Server::initCommand() {
    this->command.push_back(new Join());
    this->command.push_back(new Nick());
    this->command.push_back(new User());
    this->command.push_back(new Privmsg());
    this->command.push_back(new Invite());
    this->command.push_back(new Kick());
    this->command.push_back(new Topic());
    this->command.push_back(new Mode());
}

bool Server::parseMessage(const std::string& raw_message) {
    std::istringstream iss(raw_message);
    std::string mess;
    iss >> mess;

    for (size_t i = 0; i < mess.size(); i++) {
        if (mess[i] == this->command[i]->getName()) {
            this->command[i]->execute();
        }
    }

}

void Server::stop() {
    if (serverSocket != -1) {
        close(serverSocket);
        serverSocket = -1;
    }
    
    for (size_t i = 0; i < clientSockets.size(); ++i) {
        if (clientSockets[i] != -1) {
            close(clientSockets[i]);
        }
    }
    clientSockets.clear();
    
    std::cout << "Serveur arrêté." << std::endl;
}