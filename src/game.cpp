#include "game.hpp"

//
//-----constructor-----
//
Game::Game(){
    
    //Set Playercount
    setPlayerCount();

    //choosing Mr.X and make him players[0] for turn order
    chooseMrX();

    //Determine and assign the starting Positions to the players
    assignStartPositions();

}
//
//-----functions-----
//
void Game::addPlayer(){//Creates new Player Object and adds it to the vector
    
    Player player_tmp;
    m_players.push_back(player_tmp);
}

void Game::chooseMrX(){
    char answer_tmp;
    int answer_no;

    //Determin if Mr.X should be random
    std::cout << "Do you want to determine Mr. X randomly? [y/n] ";
    std::cin >> answer_tmp;
    if (answer_tmp == 'y'){
        answer_no = (rand() % m_players.size());
    } else {
        for (int i=0; i < m_players.size(); i++){
        std::cout << "[" << i << "] " << m_players[i].getName() << std::endl;
        }
        std::cout << "Enter the number of Mr. X: ";
        std::cin >> answer_no;
    }

    //Now Mr.X is actually set..
    m_players[answer_no].setMrX();
    std::cout << m_players[answer_no].getName() << " is Mr.X." << std::endl; //Choosing who will be Mr.X

    //Make Mr.X Player no. 0
    std::swap(m_players[m_players.size()-1], m_players[0]);
}

void Game::assignStartPositions(){
    
    //Determine starting Position

    //TODO: Fix rand() implementation, for some reason only 19 and 20 seem to get picket at the moment!
    std::vector<Location*> startingLocations = Game::m_currentMap.getStartingLocations();
    for (int i = 0; i < m_players.size(); i++){

        //Choose Random index and apply to player
        int chosenIndex = rand() % (startingLocations.size()-i); //Number of starting Positions minus current iteration (+1 because 
        m_players[i].setLocation(startingLocations[chosenIndex]);


        //Swap chosen index with last index (so it cant be chosen anymore because the sample size dereases by i)
        std::swap(startingLocations[chosenIndex], startingLocations[startingLocations.size() -1 -i]);
    }
}

void Game::movePlayer(Player* currentPlayer){
    //Display Possible moves


    

    //TODO Prüfen ob spieler sich bewegen darf und die Auswahl ermöglichen
}

//
//-----Getter-----
//
bool Game::getGameover(){
    return Game::m_gameover;
}

Player Game::getPlayer(int i){
    return Game::m_players[i];
}


//
//-----Setter-----
//
void Game::setPlayerCount(){
    std::cout << "Enter playercount (2-6): ";
    //2 to 6 players
    int playercount;
    std::cin >> playercount;

    for(int i=0; i < playercount; i++){
        Game::addPlayer();
    }
}

void Game::nextTurn(){
    m_currentTurn += 1;
    if (m_currentTurn > 23){
        m_gameover = true;
        std::cout << "Turn 23 reached. "<< m_players[0].getName() <<" won!" << std::endl;
        return;
    }
    std::cout << std::endl << "Current turn: " << m_currentTurn << std::endl;

    //Going through each players turn after another
    //Maybe somehow make it possible for players to take turns at the same time
    for (int i=0; i < m_players.size(); i++){
        std::cout << std::endl << "Player to move: " << m_players[i].getName() << std::endl;
        m_players[i].printTickets();
        //movePlayer(m_players[i]);
    }


        
        /*
        for (int i=1; i < m_players.size(); i++){
            int playertmp;
            playertmp = m_players[i].getPosition();

            for (int j=0; i < availableEdges.size();  i++ )
        }

        movePlayer(m_players[i],newPosition);
        }
        */

    
}