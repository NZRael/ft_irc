#pragma once

#include "ft_irc.hpp"

class Server {
public:
	Server(int port, const std::string& password);
	~Server();
	void run();
	void stop();

	std::string getPassword() const;
	int getPort() const;
	int getServerSocket() const;
	void initCommand();
	Channel* getChannelByName(const std::string& channelName);
	Client * getClientByNick(const std::string& clientName);

private:
	void setupSocket();
	void handleNewConnection(std::vector<pollfd>& fds);
	void handleClientMessage(std::vector<pollfd>& fds, size_t index);
	void parseMessage(int index_user, const std::string& raw_message);

	int port;
	std::string password;
	int serverSocket;
	std::vector<Client *> users;
	std::vector<Channel*> channels;

	std::vector<ACommand *> command; // initialise les classes de commandes
};

