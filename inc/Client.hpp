#pragma once

#include "ft_irc.hpp"

class Client {
private:
    int         socket;
    std::string nickname;
    std::string username;
    std::string hostname;
    std::string realname;
    bool        password;
    bool        isAuthenticated;
    std::vector<Channel*> channels;

public:
    Client(int clientSocket);
    ~Client();

    // Getters
    int getSocket() const;
    const std::string& getNickname() const;
    const std::string& getUsername() const;
    const std::string& getHostname() const;
    const std::string& getRealname() const;
    bool getPassword() const;
    bool isUserAuthenticated() const;
    const std::vector<Channel*>& getChannels() const;

    // Setters
    void setSocket(int sock);
    void setNickname(const std::string& nick);
    void setUsername(const std::string& user);
    void setHostname(const std::string& host);
    void setRealname(const std::string& real);
    void setPassword(bool pass);
    void setAuthenticated(bool auth);

    // Channel management
    void joinChannel(Channel* channel);
    void leaveChannel(Channel* channel);
    bool isInChannel(Channel* channel) const;

    // Message handling
    void sendMessage(const std::string& message) const;

    // Nouveau: méthode pour authentifier l'utilisateur
    bool authenticate(const std::string& password, Server* server);  

    
};
