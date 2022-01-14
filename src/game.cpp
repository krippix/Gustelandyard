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
    std::vector<int> startingPositions = Game::m_currentMap.getStartingPositions();
    for (int i = 0; i < m_players.size(); i++){

        //Choose Random index and apply to player
        int chosenIndex = rand() % ((startingPositions.size() -1) - i);
        m_players[i].setPosition(startingPositions[chosenIndex]);


        //Swap chosen index with last index (so it cant be chosen anymore because the sample size dereases by i)
        std::swap(startingPositions[chosenIndex], startingPositions[startingPositions.size() -1 -i]);

        //Testing stuff
        /*
        std::cout << "ChosenIndex: " << chosenIndex << "blubberbernd: " << startingPositions.size() -1 -i << std::endl;
        
        std::cout << "VEKTOR" << std::endl;
        for (int j = 0; j < startingPositions.size(); j++){
            std::cout << "[" << j << "] :"<< startingPositions[j] << std::endl;
        }
        */
    }
    std::cout << std::endl << "The players will start at the following positions: " << std::endl;
    for (int j=0; j < m_players.size(); j++){
           std::cout << m_players[j].getName() << ": " << m_currentMap.getLocationName(m_players[j].getPosition()) << std::endl;
    }
}

void Game::movePlayer(Player currentPlayer){
    int newPosition;
    std::vector<std::vector<int>> availableEdges; //[type][edge]
    std::cout << "Available Moves: " << std::endl;
    
    //Get edges of the current position
    availableEdges = m_currentMap.getAvailableEdges(currentPlayer.getPosition());

    //Mark edges where players already are, into vector occupied
    std::vector<int> occupied;
    for (int j = 1; j < m_players.size(); j++) {

        occupied.push_back(m_players[j].getPosition());//1,2,...,n
    }

    //Check each vehicle type 0->taxi 1->bus 2->train 3->boat
    //And if any of the found edges are occupied by players
    for (int k = 0; k < availableEdges.size(); k++) {

        //check each edge for current vehicle type
        for (int l = 0; l < availableEdges[k].size(); l++) {
            std::cout << l << ". " << "[" << m_currentMap.getLocationName(availableEdges[k][l]) << "]";

            switch (k) {
            case 0:
                std::cout << "[Taxi]";
                break;
            case 1:
                std::cout << "[Bus]";
                break;
            case 2:
                std::cout << "[Train]";
                break;
            case 3:
                std::cout << "[Boat]";
                break;
            }
            //check if player is next to any of those edges
            for (int m = 0; m < occupied.size(); m++) {
                if (availableEdges[k][l] == occupied[m]) { //Yes really, i want to use i
                    std::cout << "[" << m_players[m].getName() << "]";
                }
            }
            std::cout << std::endl;
        }
    }

    std::cout << "Enter your new Position: " << std::endl;
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
        movePlayer(m_players[i]);
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