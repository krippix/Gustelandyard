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