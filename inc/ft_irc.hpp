#pragma once

// Inclusions de la bibliothèque standard
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstdlib>
#include <cstdio>
#include <set>

// Déclarations anticipées
class Server;
class Client;
class Channel;
class ACommand;

// Inclusions de nos fichiers d'en-tête
#include "ACommand.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"

std::string intToString(int value);
