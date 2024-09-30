#include "../inc/Client.hpp"

Client::Client(int clientSocket) : socket(clientSocket), isAuthenticated(false) {}

Client::~Client() {
    close(socket);
}

// Getters
int Client::getSocket() const { return socket; }
const std::string& Client::getNickname() const { return nickname; }
const std::string& Client::getUsername() const { return username; }
const std::string& Client::getHostname() const { return hostname; }
const std::string& Client::getRealname() const { return realname; }
const std::string& Client::getPrefix() const { return prefix; }
bool Client::isUserAuthenticated() const { return isAuthenticated; }
const std::vector<Channel*>& Client::getChannels() const { return channels; }
std::string Client::getHistory() const { return history; }

// Setters
void Client::setSocket(int sock) { socket = sock; }
void Client::setNickname(const std::string& nick) { nickname = nick; }
void Client::setUsername(const std::string& user) { username = user; }
void Client::setHostname(const std::string& host) { hostname = host; }
void Client::setRealname(const std::string& real) { realname = real; }
void Client::setPrefix(void) {
    prefix = ":" + nickname + "!" + username + "@localhost";
}
void Client::setAuthenticated(bool auth) { isAuthenticated = auth; }
void Client::setHistory(const std::string& message) { history = message; }

// Channel management
void Client::joinChannel(Channel* channel) {
    if (std::find(channels.begin(), channels.end(), channel) == channels.end()) {
        channels.push_back(channel);
    }
}

void Client::leaveChannel(Channel* channel) {
    channels.erase(std::remove(channels.begin(), channels.end(), channel), channels.end());
}

bool Client::isInChannel(Channel* channel) const {
    return std::find(channels.begin(), channels.end(), channel) != channels.end();
}

// Message handling
void Client::sendMessage(const std::string& message) const {
    std::string finalmessage = message + "\r\n";
    send(socket, finalmessage.c_str(), finalmessage.length(), 0);
}
