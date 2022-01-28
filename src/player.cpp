#include "player.hpp"
//
//-----constructor-----
//
Player::Player(){
    //String name
    create();
};


//
//-----functions-----
//
void Player::create(){
    //Creates Player int of curren no.
    std::string name_tmp;

    std::cout << "enter name: ";
    std::cin >> name_tmp;
    setName(name_tmp);
}


void Player::useTicket(int locationType) {
    m_tickets[locationType]--;
}


void Player::addTickets(std::vector<int> newTickets) { //Adds tickets duh
    for (int i = 0; i < newTickets.size();i++) {
        m_tickets[i] += newTickets[i];
    }
}


//
//-----Getter-----
//
Location* Player::getLocation() const {
    return m_currentLocation;
}


std::string Player::getName() const {
    return Player::m_name;
}


std::vector<int> Player::getTickets() {
    return Player::m_tickets;
}


void Player::printTickets() const {
    std::cout << "Tickets: ";

    if (m_isMrX) {
        std::cout << "[black]: " << m_tickets[3] << " [2xTurn]: " << m_tickets[4];
    }
    else {
        std::cout << "[taxi]: " << m_tickets[0] << " [bus]: " << m_tickets[1] << " [train]: " << m_tickets[2];
    }
    std::cout << std::endl;
}


bool Player::isMrX() {
    if (this == nullptr) {
        return false;
    }
    else {
        return m_isMrX;
    }    
}


bool Player::isPermStuck() {
    //Checks a detective is not able to move anymore (even if a neighbouring player moves away)
    
    //This will be true if PermStuck is requested recursively
    if (m_possiblyStuck) {
        return true;
    }

    //Marks Player as possibly stuck, preventing lookup loop between players
    m_possiblyStuck = true;

    //don't check again if user is already marked stuck
    if (m_isPermStuck) {
        return true;
    }
    else {
        std::vector<Connection*> connections = m_currentLocation->getAllConnections();

        //Check if there are tickets for ANY connection, ignoring whether there is a player
        for (int i = 0; i < connections.size(); i++) {
            if (m_tickets[connections[i]->connectionType] != 0) {
                
                //Check if there is a player on this position, and if this player is stuck
                if (connections[i]->location->isOccupied()) {


                    //if player on connection is not stuck 
                    if (!(connections[i]->location->getCurrentPlayer()->isPermStuck())) {
                        m_possiblyStuck = false;
                        return false;
                    }
                }
                else {
                    //Position is free, no problem here pog
                    m_possiblyStuck = false;
                    return false;
                }
                m_possiblyStuck = false;
                return false; //If we get to this point, the current position is escapable
            }
        }
        std::cout << getName() << " will not be able to move again!" << std::endl;
        m_isPermStuck = true;
        return true;
    }
}


void Player::printMoves(Player* currentPlayer, std::vector<std::vector<Connection*>> allConnections) {
    
    //Prints out allowed moves from current Position
    std::vector<std::string> connectionTypeName{ "taxi","bus","train","boat" }; //sorry for that
    for (int i = 0; i < allConnections[1].size(); i++) {
        std::cout << i << ". ";
        std::cout << "[" << connectionTypeName[allConnections[1][i]->connectionType] << "]";
        std::cout << "[" << allConnections[1][i]->location->getName() << "]" << std::endl;
    }

    //Print out blocked/unavailable locations + Reason
    for (int i = 0; i < allConnections[0].size(); i++) {
        std::cout << allConnections[1].size() + i << ". ";
        std::cout << "[" << connectionTypeName[allConnections[1][i]->connectionType] << "]";
        
        //if player has no tickets for that position
        if (currentPlayer->getTickets()[allConnections[0][i]->connectionType] == 0) {
            std::cout << "[no tickets]" << std::endl;
        }
        //if another player is blocking the location:
        if (allConnections[0][i]->location->isOccupied()) {
            std::cout << "[" << "occupied" << "]";
            std::cout << "[" << allConnections[0][i]->location->getCurrentPlayer()->getName() << "]" << std::endl;
        }
    }
}


bool Player::isMrX_isTrapped() {
    //Checks if Mr.X is trapped between Detectives

    std::vector<Connection*> availableConnections = m_currentLocation->getEmptyConnections();
    
    if (availableConnections.size() == 0) {
        return true;
    }
    return false;
}


std::vector<std::vector<Connection*>> Player::getMoves() {
    //returns moves as 2D vector [0]Not allowed, [1]allowed

    std::vector<Connection*> availableConnections = m_currentLocation->getEmptyConnections();
    std::vector<Connection*> unavailableConnections = m_currentLocation->getOccupiedConnections();
    std::vector<std::vector<Connection*>> move_result(2);

    //Append to allowedMoves where Player has enough tickets
    //iterate through ticket types: 0->taxi, 1->bus, 2->train, 3->boat
    for (int i = 0; i <= 3; i++) {
        //check each type for Ticket availability
        if (getTickets()[i] != 0) {
            //push back all connections of the current type
            for (int j = 0; j < availableConnections.size(); j++) {
                if (availableConnections[j]->connectionType == i) {
                    move_result[1].push_back(availableConnections[j]);
                }
            }
        }
        else {
            //push back all connections of the current type, where no tickets are available
            for (int j = 0; j < availableConnections.size(); j++) {
                if (availableConnections[j]->connectionType == i) {
                    move_result[0].push_back(availableConnections[j]);
                }
            }
        }
    }
    //Push_Back occupied positions
    for (int i = 0; i < unavailableConnections.size(); i++) {
        move_result[0].push_back(unavailableConnections[i]);
    }
    return move_result;
}


//
//-----Setter-----
//
void Player::setName(std::string newname){
    //Sets name in player object
    Player::m_name = newname;
}


void Player::setMrX(){
    //makes Player Mr. X
    Player::m_isMrX = true;
    std::vector<int> xTickets {39,42,46,5,2}; //adds Tickets for Mr.X
    addTickets(xTickets);
}


void Player::setLocation(Location* newLocation){
    //Pointer to new location set on player.   
    //Keeping track of history, maybe it will be useful for visualization at some point
    if (!(m_currentLocation == nullptr))
        m_locationHistory.push_back(m_currentLocation);
    
    m_currentLocation = newLocation;
}


void Player::setPermStuck() {
    //Sets the player as permanently stuck, meaning he will not be able to move for the rest of the game.
    m_isPermStuck = true;
}