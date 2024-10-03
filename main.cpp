#include "inc/ft_irc.hpp"

bool	g_server_running = false;

void	_handleSignal(int signal) {
    g_server_running = false;
    std::cout << "Fermeture bro" << std::endl;
    (void) signal;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);
    std::string password = argv[2];

    try {
        signal(SIGINT, _handleSignal);
		signal(SIGQUIT, _handleSignal);

        Server server(port, password);
        server.run();
        
        // std::cout << "Serveur en cours d'exécution. Appuyez sur Entrée pour arrêter." << std::endl;
        // std::cin.get(); // Attend que l'utilisateur appuie sur Entrée
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
