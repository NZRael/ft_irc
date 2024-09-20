#include "../inc/Channel.hpp"

Channel::Channel(const std::string& channelName) : _name(channelName), _inviteOnly(false), _topicRestricted(false), _userLimit(0) {}

Channel::~Channel() {}

const std::string& Channel::getName() const { return _name; }
const std::string& Channel::getTopic() const { return _topic; }
const std::vector<Client*>& Channel::getUsers() const { return _users; }
bool Channel::isOperator(Client* user) const { return _operators.find(user) != _operators.end(); }
bool Channel::isInviteOnly() const { return _inviteOnly; }
bool Channel::isTopicRestricted()const { return _topicRestricted; }
unsigned int Channel::getUserLimit() const { return _userLimit; }

void Channel::setTopic(const std::string& newTopic) { _topic = newTopic; }
void Channel::setPassword(const std::string& newPassword) { _password = newPassword; }
void Channel::setInviteOnly(bool invite) { _inviteOnly = invite; }
void Channel::setUserLimit(unsigned int limit) { _userLimit = limit; }

bool Channel::addUser(Client* user)
{
	if (std::find(_users.begin(), _users.end(), user) == _users.end())
	{
		_users.push_back(user);
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
	_operators.erase(user);
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

void Channel::setMode(char mode, bool set, Client* user, const std::string& parameter)
{
	switch(mode)
	{
		case 'i':
			_inviteOnly = set;
			broadcastMessage(user->getNickname() + " set channel " + _name + " " + (set ? "+i" : "-i"));
			break;
		case 't':
			_topicRestricted = set;
			broadcastMessage(user->getNickname() + " set channel " + _name + " " + (set ? "+t" : "-t"));
			break;
		case 'k':
		if (set && !parameter.empty()) {
				_password = parameter;
				broadcastMessage(user->getNickname() + " set channel " + _name + " +k");
			} else if (!set) {
				_password.clear();
				broadcastMessage(user->getNickname() + " set channel " + _name + " -k");
			}
			break;
		// case 'o':
		// 	if (!parameter.empty()) {
		// 		Client* targetUser = server.getUserByNick(parameter);
		// 		if (targetUser && hasUser(targetUser)) {
		// 			if (set) {
		// 				addOperator(targetUser);
		// 				broadcastMessage(user->getNickname() + " gives channel operator status to " + targetUser->getNickname());
		// 			} else {
		// 				removeOperator(targetUser);
		// 				broadcastMessage(user->getNickname() + " removes channel operator status from " + targetUser->getNickname());
		// 			}
		// 		}
		// 	}
		// 	break;
		case 'l':
			if (set && !parameter.empty()) 
			{
				try 
				{
					int newLimit = std::atoi(parameter.c_str());
					if (newLimit < 0) {
						// 501 : ERR_UMODEUNKNOWNFLAG (Mode inconnu)
            			user->sendMessage(":server 501 " + user->getNickname() + " :Cannot set negative user limit");
					}
					else {
						_userLimit = newLimit;
						broadcastMessage(user->getNickname() + " set channel " + _name + " user limit to " + parameter);
					}
				} 
				catch (const std::invalid_argument& e)
				{
					// 461 : ERR_NEEDMOREPARAMS (Paramètres invalides)
        			user->sendMessage(":server 461 " + user->getNickname() + " MODE :Invalid user limit");
				} 
				catch (const std::out_of_range& e)
				{
					// 472 : ERR_UNKNOWNMODE (Mode inconnu, utilisé ici pour une valeur hors limites)
					user->sendMessage(":server 472 " + user->getNickname() + " :Client limit out of range");
				}
			} 
			else if (set) 
			{
				// Handle empty parameter
				user->sendMessage(":server 461 " + user->getNickname() + " MODE :No user limit specified");
			}
			 else 
			{
    			// 324 : RPL_CHANNELMODEIS (Réponse pour afficher le mode actuel)
    			user->sendMessage(":server 324 " + user->getNickname() + " " + _name + " +l " + intToString(_userLimit));
			}
			break;
	}
}

bool Channel::checkPassword(const std::string& attemptedPassword) const {
	return _password.empty() || attemptedPassword == _password;
}