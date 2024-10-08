#pragma once

#include "ft_irc.hpp"

class Channel {
private : 
    std::string _name;
    std::string _topic;
    std::string _topicSetter;
    time_t _topicTimestamp;
    std::time_t creationTime;
    std::vector<Client*> _users;
    std::map<Client*, bool> _operators;
    std::string _password;
    bool _inviteOnly;
    bool _topicRestricted;
    unsigned int _userLimit;
    std::set<Client*> _invitedUsers; // stocker les utilisateurs invités

public :
    Channel(const std::string& channelName);
    ~Channel();

    // Getters
    const std::string& getName() const;
    const std::string& getTopic() const;
    const std::string& getTopicSetter() const;
    time_t getTopicTimestamp() const;
    std::string getPassword() const;
    std::time_t getCreationTime() const;
    const std::vector<Client*>& getUsers() const;
    bool isOperator(Client* user) const;
    bool isInviteOnly() const;
    bool isTopicRestricted() const;
    unsigned int getUserLimit() const;

    // Setters
    void setTopic(const std::string& newTopic);
    void setTopicSetter(const std::string& setter);
    void setTopicTimestamp(time_t timestamp);
    void setPassword(const std::string& newPassword);
    void setInviteOnly(bool inviteOnly);
    void setUserLimit(unsigned int limit);

    // Client management
    bool addUser(Client* user);
    bool removeUser(Client* user);
    bool hasUser(Client* user) const;

    bool isInvited(Client* client) const;
    void inviteUser(Client* client);
    void removeInvite(Client* client);

    // Operator management
    void addOperator(Client* user);
    void removeOperator(Client* user);

    // Message broadcasting
    void broadcastMessage(const std::string& message, Client* sender = 0);

    // Mode management
    void setMode(char mode, bool set, Client* user, const std::string& parameter, Server* server);
    bool checkPassword(const std::string& attemptedPassword) const;

    bool isDigitsOnly(const std::string& str) const;
    
};
