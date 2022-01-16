#include "location.hpp"

Location::Location(int id, std::string name) {
    //Creates Object Location with id and name
    m_index = id;
    setName(name);
}


//
//-----functions-----
//
void Location::addNeighbour(ConnectionType type, Location* location) {
    m_neighbours.push_back({ type,location });
}


//
//-----getter-----
//
bool Location::isStartingPosition() const {
    return m_isStartingPosition;
}

bool Location::isOccupied() const {
    
    if (m_currentPlayer == nullptr) {
        return false;
    }
    else {
        return true;
    }
    
}

std::vector<Connection> Location::getNeighbours() const {
    //Returns Vector of neighbouring vertices
    return m_neighbours;
}

std::vector<Location*> Location::getAvailableLocations() const {
    //Returns Vector with Tuples containing location and a bool, true->free, false->occupied
    //this function will ONLY check if the node can be used. Tickets will probably have to be checked in the player object
    std::vector<Location*> availableLocations;

    //Adds moves as tuples to result vector
    for (int i = 0; i < m_neighbours.size(); i++) {
        if (m_neighbours[i].location->isOccupied()) {
            availableLocations.push_back(m_neighbours[i].location);
        }
    }
    return availableLocations;
}

std::vector<Location*> Location::getOccupiedLocations() const {
    //Invalid Version of valid Moves :P
    std::vector<Location*> occupiedLocations;

    //Adds moves as tuples to result vector
    for (int i = 0; i < m_neighbours.size(); i++) {
        if (m_neighbours[i].location->isOccupied()) {
            occupiedLocations.push_back(m_neighbours[i].location);
        }
    }
    return occupiedLocations;
}

//
//-----setter-----
//
void Location::setName(std::string name) {
    m_name = name;
}

void Location::setCurrentPlayer(const Player* currentPlayer) {
    //Adds pointer to player on this location
    const Player* m_currentPlayer = currentPlayer;
    m_currentPlayer->getName();
}

void Location::setStartingPosition() {
    m_isStartingPosition = true;
}