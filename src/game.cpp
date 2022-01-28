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

        //Swap chosen index with last index (so it cant be chosen anymore because the sample size dereases by i)
        std::swap(startingLocations[chosenIndex], startingLocations[startingLocations.size() -1 -i]);
    }
}


void Game::nextTurn() {
    m_currentTurn += 1;

    std::cout << "#####################################" << std::endl;

    //Announce Mr. X's position, win game based on turn.
    switch (m_currentTurn) {
    case 3:
    case 8:
    case 13:
    case 18:
        std::cout << "Turn " << m_currentTurn << " reached! Mr.X is currently in/at: " << m_players[0].getLocation()->getName() << std::endl;
        break;
    case 24:
        std::cout << "Turn 24 reached! Mr. X escaped from " << m_players[0].getLocation()->getName() << std::endl;
        m_gameover = true;
        return;
    default:
        std::cout << "Turn " << m_currentTurn << " started!" << std::endl;
    }

    //Check if Mr. X is trapped
    if (m_players[0].isMrX_isTrapped()) {
        std::cout << "Mr.X is trapped at " << m_players[0].getLocation()->getName() << "the detectives have won!" << std::endl;
        m_gameover = true;
        return;
    }
    
    //Check if detectives can still move
    if (isEveryoneStuck()) {
        m_gameover = true;
        std::cout << "All detectives are stuck! Mr. X has won the game!" << std::endl;
        return;
    }

    //Going through each players turn after another
    //Maybe somehow make it possible for players to take turns at the same time
    for (int i = 0; i < m_players.size(); i++) {
        if (m_gameover) {
            return;
        }
        std::cout << std::endl << "Player to move: " << m_players[i].getName() << std::endl;
        std::cout << std::endl << "Current Location: " << m_players[i].getLocation()->getName() << std::endl;
        movePlayer(&m_players[i]);
        std::cout << std::endl;
    }
}


void Game::movePlayer(Player* currentPlayer){
    //Player movement, and most of the gameplay. Returns false, once somebody won.
    
    //Print available Tickets
    currentPlayer->printTickets();

    //Get all moves [0] Disallowed [1]allowed
    std::vector<std::vector<Connection*>> allMoves = currentPlayer->getMoves();
    
    //Print out moves
    currentPlayer->printMoves(currentPlayer, allMoves);

    //Check if player has been trapped
    if (allMoves[1].size() == 0) {
        std::cout << "No available Moves! You are stuck here!" << std::endl;
        setLocation(currentPlayer,currentPlayer->getLocation()); //For History keeping
        return;
    }

    //Player input
    std::cout << "Move to: ";
    int selection;
    
    do {
        std::cin >> selection;
        if (selection < 0 || selection > allMoves[1].size()) {
            std::cout << "Not a valid move, try again:";
        }
    } while (selection < 0 || selection > allMoves[1].size());
    
    //Now that selection was made, the actual movement can happen
    //But first we have to check if the player moved to Mr.X's location
    if (allMoves[1][selection]->location->getCurrentPlayer()->isMrX()) {
        currentPlayer->setLocation(allMoves[1][selection]->location);
        std::cout << "You found " << m_players[0].getName() << "!" << std::endl;
        std::cout << "The detectives have won the game!" << std::endl;
        m_gameover = true;
    }
    
    //Now everything should be fine? Please?
    currentPlayer->useTicket(allMoves[1][selection]->connectionType);
    setLocation(currentPlayer, allMoves[1][selection]->location);
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


bool Game::isEveryoneStuck() {
    //Check if every player (who isn't Mr.X) is stuck
    for (int i = 1; i < m_players.size(); i++) {
        if (!(m_players[i].isPermStuck())) {
            return false;
        }
    }
    return true;
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


void Game::setLocation(Player* currentPlayer, Location* newLocation) { //Needed, because location has to be saved in Location AND in player object
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