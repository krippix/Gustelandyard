#include "game.hpp"

//
//-----constructor-----
//


//
//-----functions-----
//
void Game::start() {
    //incease turns until game is set to gameover

    if (m_isHost) {
        host();
    }
    else {
        //join();
    }

    //Set Playercount
    setPlayerCount();

    //choosing Mr.X and make him players[0] for turn order
    chooseMrX();

    //Determine and assign the starting Positions to the players
    assignStartPositions();
}

void Game::host() {
    //Generate Game PIN, and display it
    generatePin();


}

void Game::addPlayer(bool ownUser) {
    //Creates new Player Object and adds it to the vector
    //If the ownUser tag is set, it will create the user locally, otherwise it will wait for incoming connections

    if (ownUser) {
        Player player_tmp;
        m_players.push_back(player_tmp);
    }
    else {
        //handle incoming socket connections
        //Player player_tmp(name);
        //m_players.push_back();
    }
}

void Game::chooseMrX() {
    char answer_tmp;
    int answer_no;

    //Determine if Mr.X should be random
    std::cout << "Do you want to determine Mr. X randomly? [y/n] ";
    std::cin >> answer_tmp;
    if (answer_tmp == 'y') {
        //Random wizardry
        answer_no = randomInteger(0, m_players.size() - 1);

    }
    else {
        for (int i = 0; i < m_players.size(); i++) {
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

void Game::assignStartPositions() {
    //Good luck using this again
    std::default_random_engine engine(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

    //Determine starting Position

    //TODO: Fix rand() implementation, for some reason only 19 and 20 seem to get picket at the moment!
    std::vector<Location*> startingLocations = Game::m_currentMap.getStartingLocations();

    for (int i = 0; i < m_players.size(); i++) {

        //Choose Random index and apply to player
        //Number of starting Positions minus current iteration (+1 because 
        std::uniform_int_distribution<int> range(0, startingLocations.size() - i - 1);

        int chosenIndex = range(engine);
        setLocation(&m_players[i], startingLocations[chosenIndex]);

        //Swap chosen index with last index (so it cant be chosen anymore because the sample size dereases by i)
        std::swap(startingLocations[chosenIndex], startingLocations[startingLocations.size() - 1 - i]);
    }
}

void Game::nextTurn() {
    m_currentTurn += 1;

    std::cout << "#####################################" << std::endl;

    //End based on turn
    if (m_currentTurn == 23) {
        std::cout << "Turn 23 reached! Mr. X escaped from " << m_players[0].getLocation()->getName() << std::endl;
        m_gameover = true;
        return;
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

    //Announce currentTurn
    std::cout << "Turn: " << m_currentTurn << std::endl;


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

void Game::movePlayer(Player* currentPlayer) {
    //Player movement, and most of the gameplay. Returns false, once somebody won.

    //Print available Tickets
    currentPlayer->printTickets();

    //Get all moves [0] Disallowed [1]allowed
    std::vector<std::vector<Connection*>> allMoves = currentPlayer->getMoves();

    //Print Black Ticket
    if (currentPlayer->getTickets()[3] != 0) {
        std::cout << "-1. [2x Ticket]" << std::endl;
    }

    //Print out moves
    currentPlayer->printMoves(currentPlayer, allMoves);

    //Check if player has been trapped
    if (allMoves[1].size() == 0) {
        std::cout << "No available Moves! You are stuck here!" << std::endl;
        setLocation(currentPlayer, currentPlayer->getLocation()); //For History keeping
        return;
    }

    //Player input
    std::cout << "Move to: ";
    int selection;

    bool validInput = false;

    do {
        std::cin.clear();
        std::cin >> selection;
        if (selection >= 0 && selection < allMoves[1].size() || ((currentPlayer->getTickets()[3] != 0) && selection == -1)) {
            if (currentPlayer->getActiveDoubleMove() && selection == -1) {
                validInput = false;
                std::cout << "You can only 2x move once per round!" << std::endl;
                std::cout << "Try again: ";
            }
            else {
                validInput = true;
            }
        }
        else {
            std::cout << "Invalid input, try again: ";
        }

    } while (!validInput);

    if (selection == -1) {
        currentPlayer->setActiveDoubleMove(true);
        movePlayer(currentPlayer);
        movePlayer(currentPlayer);
        currentPlayer->setActiveDoubleMove(false);
        return;
    }

    //Now that selection was made, the actual movement can happen
    //But first we have to check if the player moved to Mr.X's location
    if (allMoves[1][selection]->location->getCurrentPlayer()->isMrX()) {
        currentPlayer->setLocation(allMoves[1][selection]->location);
        std::cout << "You found " << m_players[0].getName() << "!" << std::endl;
        std::cout << "The detectives have won the game!" << std::endl;
        m_gameover = true;
    }

    //Uses Ticket for the move
    currentPlayer->useTicket(allMoves[1][selection]->connectionType);

    setLocation(currentPlayer, allMoves[1][selection]->location);

    //Announce Mr.X if in key round
    if (currentPlayer->isMrX()) {
        announceMrXposition();
    }
    return;
}

void Game::announceMrXposition() {
    //Announce Mr. X's position, win game based on turn.
    int moveNr = m_players[0].getHistorySize();

    switch (moveNr) {
    case 3:
        std::cout << "Mr.X made his " << moveNr << "rd move, he is located at: " << m_players[0].getLocation()->getName() << std::endl;
        break;
    case 8:
    case 13:
    case 18:
    case 24:
        std::cout << "Mr.X made his " << moveNr << "th move, he is located at: " << m_players[0].getLocation()->getName() << std::endl;
        break;
    }
}

int Game::randomInteger(int x, int y) {
    //Generates random int between x and y

    //Yes, nanoseconds.
    std::default_random_engine engine(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
    std::uniform_int_distribution<int> range(x, y);

    return range(engine);
}

void Game::generatePin() {
    //Generate Game PIN between 10000 and 99999
    m_gamepin = randomInteger(10000, 99999);
    std::cout << "Game PIN: " << m_gamepin << std::endl;
}

//
//-----Getter-----
//
bool Game::getGameover() {
    return Game::m_gameover;
}

Player Game::getPlayer(int i) {
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

int Game::getGamePIN() {
    return m_gamepin;
}

//
//-----Setter-----
//
void Game::setHosted() {
    m_isHost = true;
}

void Game::setPlayerCount() {
    std::cout << "Enter playercount (2-6): ";
    //2 to 6 players
    int playercount;
    std::cin >> playercount;

    for (int i = 0; i < playercount; i++) {
        addPlayer(true);
    }
}

void Game::setLocation(Player* currentPlayer, Location* newLocation) { //Needed, because location has to be saved in Location AND in player object
    //clear old location

    if (!(currentPlayer->getLocation() == nullptr)) {
        currentPlayer->getLocation()->setCurrentPlayer(nullptr); //Makes old position empty!
    }

    //Sets Location on Player object
    newLocation->setCurrentPlayer(currentPlayer);

    //Sets location on Location object
    currentPlayer->setLocation(newLocation);
}