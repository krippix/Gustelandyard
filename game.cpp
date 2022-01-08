#include "game.hpp"

//
//-----constructor-----
//
Game::Game(){
    std::cout << "Anzahl der Spieler: ";
    //2 to 6 players
    int playercount;
    std::cin >> playercount;

    for(int i=0; i < playercount; i++){
        Game::addPlayer();
    }
    std::cout << players[chooseMrX()].getName() << " ist Mr.X." << std::endl; //Choosing who will be Mr.X

    //Determine starting Position
    std::vector<int> startingPositions = Game::currentMap.getStartingPositions();

    //TODO: Pick starting Position for each player, without assigning them twice
    for

}
//
//-----functions-----
//
void Game::addPlayer(){//Creates new Player Object and adds it to the vector
    
    Player player_tmp;
    players.push_back(player_tmp);
}

int Game::chooseMrX(){
    char answer_tmp;
    std::cout << "Soll Mr.X durch Zufall bestimmt werden? [y/n] ";
    std::cin >> answer_tmp;
    if (answer_tmp == 'y'){
        return (rand() % players.size());
    }

    for (int i=0; i < players.size(); i++){
        std::cout << "[" << i << "] " << players[i].getName() << std::endl;
    }
    int answer_no;
    std::cout << "Wer soll Mr.X sein? Bitte gib die Nummer des Spielers an: ";
    std::cin >> answer_no;
    players[answer_no].setMrX();
    return answer_no;
}

//
//-----Getter-----
//
bool Game::getGameover(){
    return Game::m_gameover;
}

Player Game::getPlayer(int i){
    return Game::players[i];
}


//
//-----Setter-----
//


