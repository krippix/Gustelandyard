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
    std::cout << "Soll Mr.X durch Zufall bestimmt werden? [y/n] ";
    std::cin >> answer_tmp;
    if (answer_tmp == 'y'){
        answer_no = (rand() % m_players.size());
    } else {
        for (int i=0; i < m_players.size(); i++){
        std::cout << "[" << i << "] " << m_players[i].getName() << std::endl;
        }
        std::cout << "Wer soll Mr.X sein? Bitte gib die Nummer des Spielers an: ";
        std::cin >> answer_no;
    }

    //Now Mr.X is actually set..
    m_players[answer_no].setMrX();
    std::cout << m_players[answer_no].getName() << " ist Mr.X." << std::endl; //Choosing who will be Mr.X

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
    std::cout << "The players will start at the following positions: " << std::endl;
    for (int j=0; j < m_players.size(); j++){
           std::cout << m_players[j].getName() << ": " << m_players[j].getPosition() << std::endl;
    }
}

void movePlayer(Player currentPlayer, int newPosition){

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
    std::cout << "Anzahl der Spieler (2-6): ";
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

    //Moving each player after each other. (Mr.X first as he is always no. 0)
    std::vector<std::vector<int>> availableEdges; //[type][edge]
    for (int i=0; i < m_players.size(); i++){
        int newPosition;
        
        std::cout << "Available Moves for " << m_players[i].getName() << std::endl;
        //Get edges from current position
        availableEdges = m_currentMap.getEdges(m_players[i].getPosition());
        
        //Mark edges where players already are, into vector occupied
        std::vector<int> occupied;
        for (int j=1; j < m_players.size(); j++){
            
            occupied.push_back(m_players[j].getPosition());//1,2,...,n
        }
        
        //Check each vehicle type 0->taxi 1->bus 2->train 3->boat
        for (int k=0; k < availableEdges.size(); k++){

            //check each edge for current vehicle type
            for ( int l=0; l < availableEdges[k].size(); l++){
                std::cout << "[" << availableEdges[k][l] << "]";

                
                switch (k){
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
                for (int m=0; m < occupied.size(); m++){
                    if(availableEdges[k][l] == occupied[m]){ //Yes really, i want to use i
                        std::cout << "[" << m_players[m].getName() << "]";
                    }
                }
                std::cout << std::endl;
            }
        }
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

    std::cout << "Current turn: " << m_currentTurn << std::endl;
}