#pragma once

#include "Client.hpp"
#include "Join.hpp"
#include "Nick.hpp"
#include "Pass.hpp"
#include "Invite.hpp"
#include "Kick.hpp"
#include "Topic.hpp"
#include "Mode.hpp"
#include "Privmsg.hpp"
#include "User.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


class Client;

class ACommand {
public:
    ACommand();
    ~ACommand();

    std::string getName() const;
    virtual void execute(Client *user, std::string raw_message) = 0;
protected:
    std::string _Name;
    bool _isValid;
};
