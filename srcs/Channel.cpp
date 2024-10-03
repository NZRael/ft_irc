#include "../inc/Channel.hpp"

Channel::Channel(const std::string& channelName) : _name(channelName), creationTime(std::time(0)), _inviteOnly(false), _topicRestricted(true), _userLimit(0) {}

Channel::~Channel() {}

const std::string& Channel::getName() const { return _name; }
const std::string& Channel::getTopic() const { return _topic; }
const std::string& Channel::getTopicSetter() const { return _topicSetter; }
time_t	Channel::getTopicTimestamp() const { return _topicTimestamp; }
std::string Channel::getPassword() const { return _password; }
std::time_t Channel::getCreationTime() const { return creationTime; }
const std::vector<Client*>& Channel::getUsers() const { return _users; }
unsigned int Channel::getUserLimit() const { return _userLimit; }
bool Channel::isOperator(Client* user) const {
	if (hasUser(user))
		return _operators.at(user);
	return false;
}
bool Channel::isInviteOnly() const { return _inviteOnly; }
bool Channel::isTopicRestricted()const { return _topicRestricted; }
void Channel::setTopic(const std::string& newTopic) { _topic = newTopic; }
void Channel::setTopicSetter(const std::string& setter) { _topicSetter = setter; }
void Channel::setTopicTimestamp(time_t timestamp) { _topicTimestamp = timestamp; }
void Channel::setPassword(const std::string& newPassword) { _password = newPassword; }
void Channel::setInviteOnly(bool invite) { _inviteOnly = invite; }
void Channel::setUserLimit(unsigned int limit) { _userLimit = limit; }

bool Channel::addUser(Client* user)
{
	if (std::find(_users.begin(), _users.end(), user) == _users.end())
	{
		_users.push_back(user);
		_operators[user] = false;
		return (true);
	}
	return (false);
}

bool Channel::removeUser(Client* user)
{
	std::vector<Client*>::iterator it = std::find(_users.begin(), _users.end(), user);
	if (it != _users.end())
	{
		_users.erase(it);
		_operators.erase(user);
		
		return (true);
	}
	return (false);
}

bool Channel::hasUser(Client* user) const
{
	return std::find(_users.begin(), _users.end(), user) != _users.end();
}

void Channel::addOperator(Client* user)
{
	if (hasUser(user))
		_operators[user] = true;
}

void Channel::removeOperator(Client* user)
{
	_operators[user] = false;
}

void Channel::broadcastMessage(const std::string& message, Client* sender)
{
	for (std::vector<Client*>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		Client* user = *it;
		if (user != sender) 
			user->sendMessage(message);
	}
}

void Channel::setMode(char mode, bool set, Client* user, const std::string& parameter, Server* server)
{
	switch(mode)
	{
		case 'i':
			_inviteOnly = set;
			broadcastMessage(user->getPrefix() + " MODE " + _name + " " + (set ? "+i" : "-i"));
			break;
		case 't':
			_topicRestricted = set;
			broadcastMessage(user->getPrefix() + " MODE " + _name + " " + (set ? "+t" : "-t"));
			break;
		case 'k':
			if (set && !parameter.empty()) {
				_password = parameter;
				broadcastMessage(user->getPrefix() + " MODE " + _name + " +k " + _password);
			} else if (!set) {
				_password.clear();
				broadcastMessage(user->getPrefix() + " MODE " + _name + " -k");
			}
			break;
		case 'o':
			if (!parameter.empty()) {
				Client* targetUser = server->getClientByNick(parameter);
				if (targetUser && hasUser(targetUser)) {
					if (set) {
						addOperator(targetUser);
						broadcastMessage(user->getPrefix() + " MODE " + _name + " +o " + targetUser->getNickname());
					} else {
						removeOperator(targetUser);
						broadcastMessage(user->getPrefix() + " MODE " + _name + " -o " + targetUser->getNickname());
					}
				}
			}
			break;
		case 'l':
			if (set && !parameter.empty()) 
			{
				long int newLimit = std::atoi(parameter.c_str());
				if (newLimit < 0) {
            		user->sendMessage(":server 501 " + user->getNickname() + " :Cannot set negative user limit");
					break ;
				}
				if (!isDigitsOnly(parameter))
				{
					user->sendMessage(":server 461 " + user->getNickname() + " MODE :Invalid user limit");
					break;
				}

				if (parameter.size() > 8)
				{
					user->sendMessage(":server 472 " + user->getNickname() + " :Client limit out of range");
					break;
				}
				_userLimit = newLimit;
				broadcastMessage(user->getPrefix() + " MODE " + _name + " +l " + parameter);
			} 
			else if (set) 
			{
				user->sendMessage(":server 461 " + user->getNickname() + " MODE :No user limit specified");
			}
			else if (!set && parameter.empty() && _userLimit != 0)
			{
				_userLimit = 0;
				broadcastMessage(user->getPrefix() + " MODE " + _name + " -l ");
			}
			break;
	}
}

bool Channel::checkPassword(const std::string& attemptedPassword) const {
	return _password.empty() || attemptedPassword == _password;
}

bool Channel::isInvited(Client* client) const {
    return _invitedUsers.find(client) != _invitedUsers.end();
}

void Channel::inviteUser(Client* client) {
    _invitedUsers.insert(client);
}

void Channel::removeInvite(Client* client) {
    _invitedUsers.erase(client);
}

bool Channel::isDigitsOnly(const std::string& str) const{
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
