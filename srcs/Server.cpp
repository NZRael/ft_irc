#include "../inc/Server.hpp"
#include "../inc/Join.hpp"
#include "../inc/Nick.hpp"
#include "../inc/Pass.hpp"
#include "../inc/Privmsg.hpp"
#include "../inc/Topic.hpp"
#include "../inc/User.hpp"
#include "../inc/Mode.hpp"
#include "../inc/Invite.hpp"
#include "../inc/Kick.hpp"
#include "../inc/Ping.hpp"

std::string intToString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

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
        ret = 0;
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
        std::string clientId = std::string(clientIP) + ":" + intToString(ntohs(clientAddr.sin_port));
        
        std::cout << "Nouvelle connexion acceptée de " << clientId << std::endl;
        
        pollfd clientPollFd;
        clientPollFd.fd = clientSocket;
        clientPollFd.events = POLLIN;
        fds.push_back(clientPollFd);
        users.push_back(new Client(clientSocket));
    }
}

void Server::handleClientMessage(std::vector<pollfd>& fds, size_t index) {
    char buffer[4096];
    int clientSocket = fds[index].fd;
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    size_t index_user = 0;
    for (; index_user < users.size(); ++index_user) {
        if (users[index_user]->getSocket() == clientSocket) {
            break;
        }
    }
    if (index_user >= users.size()) {
        std::cerr << "Erreur : Client non trouvé pour le socket " << clientSocket << std::endl;
        return;
    }
    if (bytesRead <= 0) {
        std::cout << "Connexion fermée pour le user n°" << users[index_user]->getSocket() << std::endl;
        delete users[index_user];
        users.erase(users.begin() + index_user);
        close(clientSocket);
        fds.erase(fds.begin() + index);
    } else {
        buffer[bytesRead] = '\0';
        std::cout << "Reçu de l'utilisateur n°" << users[index_user]->getSocket() << " : " << buffer << std::endl;
        parseMessage(index_user, buffer);
    }
}

// fonction void qui va instancier la class ACommand avec toutes les commandes ex: this->command.push_back(new JoinCommand());
void Server::initCommand() {
    command.push_back(new Nick());
    command.push_back(new User());
    command.push_back(new Privmsg());
    command.push_back(new Invite());
    command.push_back(new Kick());
    command.push_back(new Topic());
    command.push_back(new Mode());
    command.push_back(new Join());
    command.push_back(new Pass());
    command.push_back(new Ping());
}

void Server::parseMessage(int index_user, const std::string& raw_message) {
    if (this->command.empty()) {
        initCommand();
    }
    std::vector<std::string> c_commandes;
    std::string ligne;
    std::istringstream iss(raw_message);
    while (std::getline(iss, ligne)) {
        c_commandes.push_back(ligne);
    }
    for (size_t i = 0; i < c_commandes.size(); i++) {
        if (c_commandes[i].find("CAP LS") != std::string::npos) {
            users[index_user]->sendMessage("CAP * LS\r\n");
            continue ;
        }
        std::istringstream iss(c_commandes[i]);
        std::string mess;
        iss >> mess;
        for (size_t i = 0; i < this->command.size(); i++) {
            if (mess == this->command[i]->getName()) {
                std::string reste;
                std::getline(iss, reste);
                reste.erase(0, reste.find_first_not_of(" "));
                reste.erase(reste.find_last_not_of("\r") + 1);
                this->command[i]->execute(users[index_user], reste, this);
            }
        }
    }
}

void Server::stop() {
    if (serverSocket != -1) {
        close(serverSocket);
        serverSocket = -1;
    }
    for (size_t i = 0; i < users.size(); ++i) {
            delete(users[i]);
    }
    std::cout << "Serveur arrêté." << std::endl;
}

std::string Server::getPassword() const{
    return(password);
}

int Server::getPort() const{
    return(port);
}

int Server::getServerSocket() const{
    return(serverSocket);
}

Channel* Server::getChannelByName(const std::string& channelName)
{
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it ++)
    {
        if ((*it)->getName() == channelName)
            return (*it);
    }
    return NULL; 
}

Client * Server::getClientByNick(const std::string& clientName)
{
    for (std::vector<Client*>::iterator it = users.begin(); it != users.end(); it++)
    {
        if ((*it)->getNickname() == clientName)
            return (*it);
    }
    return NULL;
}

void Server::addChannel(Channel* channel) {
    channels.push_back(channel);
}

bool Server::isNicknameUsed(const std::string& nick) {
    for (std::vector<Client*>::iterator it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getNickname() == nick) {
            return true;
        }
    }
    return false;
}
