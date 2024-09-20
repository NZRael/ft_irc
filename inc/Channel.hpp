#pragma once

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include "Client.hpp"

class Channel {
private : 
    std::string _name;
    std::string _topic;
    std::vector<Client*> _users;
    std::map<Client*, bool> _operators;
    std::string _password;
    bool _inviteOnly;
    bool _topicRestricted;
    unsigned int _userLimit;

public :
    Channel(const std::string& channelName);
    ~Channel();

    // Getters
    const std::string& getName() const;
    const std::string& getTopic() const;
    const std::vector<Client*>& getUsers() const;
    bool isOperator(Client* user) const;
    bool isInviteOnly() const;
    bool isTopicRestricted() const;
    unsigned int getUserLimit() const;

    // Setters
    void setTopic(const std::string& newTopic);
    void setPassword(const std::string& newPassword);
    void setInviteOnly(bool inviteOnly);
    void setUserLimit(unsigned int limit);

    // Client management
    bool addUser(Client* user);
    bool removeUser(Client* user);
    bool hasUser(Client* user) const;

    // Operator management
    void addOperator(Client* user);
    void removeOperator(Client* user);

    // Message broadcasting
    void broadcastMessage(const std::string& message, Client* sender = 0);

    // Mode management
    void setMode(char mode, bool set, Client* user, const std::string& parameter);
    bool checkPassword(const std::string& attemptedPassword) const;
    
};