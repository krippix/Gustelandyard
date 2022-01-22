#include "game.hpp"
#include <random>
#include <chrono>

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

    std::default_random_engine engine(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

    //Determin if Mr.X should be random
    std::cout << "Do you want to determine Mr. X randomly? [y/n] ";
    std::cin >> answer_tmp;
    if (answer_tmp == 'y'){
        //Random wizardry, seriously fuck this
        std::uniform_int_distribution<int> range(0, m_players.size() - 1);
        answer_no = range(engine);
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
    std::swap(m_players[answer_no], m_players[0]);
}

void Game::assignStartPositions(){
    //Good luck using this again
    std::default_random_engine engine(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
    
    //Determine starting Position

    //TODO: Fix rand() implementation, for some reason only 19 and 20 seem to get picket at the moment!
    std::vector<Location*> startingLocations = Game::m_currentMap.getStartingLocations();

    for (int i = 0; i < m_players.size(); i++){
        
        //Choose Random index and apply to player
        //Number of starting Positions minus current iteration (+1 because 
        std::uniform_int_distribution<int> range(0, startingLocations.size() - i - 1); 

        int chosenIndex = range(engine);
        setLocation(&m_players[i], startingLocations[chosenIndex]);
        std::cout << ":thonk:" << chosenIndex << std::endl;

        //Swap chosen index with last index (so it cant be chosen anymore because the sample size dereases by i)
        std::swap(startingLocations[chosenIndex], startingLocations[startingLocations.size() -1 -i]);
    }
}

void Game::movePlayer(Player* currentPlayer){
    //Player movement, and most of the gameplay. Returns false, once somebody won.
    
    //"Input" Stuff
    std::vector <Connection*> availableConnections = currentPlayer->getLocation()->getAvailableConnections();
    std::vector <Connection*> unavailableConnections = currentPlayer->getLocation()->getOccupiedConnections();
    //Result Vector
    std::vector<Connection*> allowedMoves; //This vector will contain all possible connections
    std::vector<Connection*> disallowedMoves; //duh
    
    //check if Mr.X has been trapped
    if (availableConnections.size() == 0 && currentPlayer->isMrX()) {
        std::cout << "Mr.X is trapped at " << currentPlayer->getLocation()->getName() << "the detectives have won!" << std::endl;
        setLocation(currentPlayer, currentPlayer->getLocation());
        m_gameover = true;
        return;
    }


    //Append to allowedMoves where Player has enough tickets
    //iterate through ticket types: 0->taxi, 1->bus, 2->train, 3->boat
    for (int i = 0; i <= 3; i++) {
        
        //check each type for Ticket availability
        if (currentPlayer->getTickets()[i] != 0) {
            //push back all connections of the current type
            for (int j = 0; j < availableConnections.size(); j++) {
                if (availableConnections[j]->connectionType == i) {
                    allowedMoves.push_back(availableConnections[j]);
                }
                                
            }       
        }
        else {
            //push back all connections of the current type
            for (int j = 0; j < availableConnections.size(); j++) {
                if (availableConnections[j]->connectionType == i) {
                    disallowedMoves.push_back(availableConnections[j]);
                }

            }
        }   
    }
    //Print out legal moves
    std::vector<std::string> connectionTypeName{ "taxi","bus","train","boat" }; //sorry for that
    for (int i = 0; i < allowedMoves.size(); i++) {
        std::cout << i << ". ";
        std::cout << "[" << connectionTypeName[allowedMoves[i]->connectionType] << "]";
        std::cout << "[" << allowedMoves[i]->location->getName() << "]" << std::endl;
    }
    
    //Print out illegal moves
    //First occupied places
    for (int i = 0; i < unavailableConnections.size(); i++) {
        std::cout << unavailableConnections.size()+i << ". ";
        std::cout << "[" << connectionTypeName[unavailableConnections[i]->connectionType] << "]";
        std::cout << "[" << unavailableConnections[i]->location->getName() << "][blocked]";
        std::cout << "[" << unavailableConnections[i]->location->getCurrentPlayer()->getName() << "]" << std::endl;
    }
    
    //Now those that are unreachable due to missing tickets
    for (int i = 0; i < disallowedMoves.size(); i++) {
        std::cout << disallowedMoves.size() + unavailableConnections.size() + i << ". ";
        std::cout << "[" << connectionTypeName[disallowedMoves[i]->connectionType] << "]";
        std::cout << "[" << disallowedMoves[i]->location->getName() << "][no tickets]" << std::endl;
    }

    //Player input
    int selection;

    //Check if player has been trapped
    if (allowedMoves.size() == 0) {
        std::cout << "No available Moves! You are stuck here!" << std::endl;
        setLocation(currentPlayer,currentPlayer->getLocation()); //For History keeping
        return;
    }

    std::cout << "Move to: ";
    do {
        std::cin >> selection;
        if (selection < 0 || selection > allowedMoves.size()) {
            std::cout << "Input out of range, try again:";
        }
    } while (selection < 0 || selection > allowedMoves.size());
    
    //Now that selection was made, the actual movement can happen
    //But first we have to check if the player moved to Mr.X's location
    if (allowedMoves[selection]->location->getCurrentPlayer()->isMrX()) {
        currentPlayer->setLocation(allowedMoves[selection]->location);
        std::cout << "You found " << m_players[0].getName() << "!" << std::endl;
        std::cout << "The detectives have won the game!" << std::endl;
        m_gameover = true;
    }
    
    //Now everything should be fine? Please?
    setLocation(currentPlayer, allowedMoves[selection]->location);
    return;
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

    std::cout << "#####################################" << std::endl;

    if (m_currentTurn > 23){
        m_gameover = true;
        std::cout << "Turn 23 reached. "<< m_players[0].getName() <<" won!" << std::endl;
        return;
    }
    std::cout << "Turn " << m_currentTurn << " started!" << std::endl;

    //Going through each players turn after another
    //Maybe somehow make it possible for players to take turns at the same time
    for (int i=0; i < m_players.size(); i++){
        std::cout << std::endl << "Player to move: " << m_players[i].getName() << std::endl;
        std::cout << std::endl << "Current Location: " << m_players[i].getLocation()->getName() << std::endl;
        m_players[i].printTickets();
        movePlayer(&m_players[i]);
        std::cout << std::endl;
    }  
}

void Game::setLocation(Player* currentPlayer, Location* newLocation) { //Needet, because location has to be saved in Location AND in player object
    //clear old location
    
    if (!(currentPlayer->getLocation() == nullptr)){
        currentPlayer->getLocation()->setCurrentPlayer(nullptr); //Makes old position empty!
    }

    //Sets Location on Player object
    newLocation->setCurrentPlayer(currentPlayer);

    if (newLocation->getCurrentPlayer() == nullptr) {
        std::cout << "THIS SHOULDNT HAPPEN D: WHAT IS GOING ON REEEEEEEEE" << std::endl;
    }
                                                                       
    //Sets location on Location object
    currentPlayer->setLocation(newLocation);
    
    
}