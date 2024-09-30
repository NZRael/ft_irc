#pragma once

#include "ft_irc.hpp"

class Client {
private:
    int         socket;
    std::string nickname;
    std::string username;
    std::string hostname;
    std::string realname;
    std::string prefix;
    bool        isAuthenticated;
    std::vector<Channel*> channels;
    std::string history;

public:
    Client(int clientSocket);
    ~Client();

    // Getters
    int getSocket() const;
    const std::string& getNickname() const;
    const std::string& getUsername() const;
    const std::string& getHostname() const;
    const std::string& getRealname() const;
    const std::string& getPrefix() const;
    bool isUserAuthenticated() const;
    const std::vector<Channel*>& getChannels() const;
    std::string getHistory() const;

    // Setters
    void setSocket(int sock);
    void setNickname(const std::string& nick);
    void setUsername(const std::string& user);
    void setHostname(const std::string& host);
    void setRealname(const std::string& real);
    void setPrefix(void);
    void setAuthenticated(bool auth);
    void setHistory(const std::string& message);

    // Channel management
    void joinChannel(Channel* channel);
    void leaveChannel(Channel* channel);
    bool isInChannel(Channel* channel) const;

    // Message handling
    void sendMessage(const std::string& message) const;    
};
