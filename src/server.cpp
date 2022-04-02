#include "server.hpp"

void Server::startSession() {
    generatePin();

    //TODO: Implement encryption

    //TODO: Register @ matchmaking server?

    Game game;
    
    // Host adds himself as player
    game.addPlayerHost();




    // choose Mr.X n' stuff
    game.prepare();
}

void Server::generatePin() {
    //Generate Game PIN between 10000 and 99999
    m_sessionPin = Game::randomInteger(10000, 99999);
    std::cout << "Game PIN: " << m_sessionPin << std::endl;
}