#include "location.hpp"

Location::Location(int id, std::string name) {
    //Creates Object Location with id and name
    m_index = id;
    setName(name);
}


//
//-----functions-----
//
void Location::addNeighbour(int type, Location* location) {
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


const std::vector<Connection*> Location::getAllConnections(){
    //Returns Vector of neighbouring vertices
    std::vector<Connection*> allConnections;

    for (int i = 0; i < m_neighbours.size(); i++) {
        allConnections.push_back(&m_neighbours[i]);
    }
    return allConnections;
}


const std::vector<Connection*> Location::getEmptyConnections() {
    //returns vector with Connections to neighbours
    std::vector<Connection*> availableConnections;

    //Returns Pointer to the connection, if not occupied or occupying player is Mr.X
    for (int i = 0; i < m_neighbours.size(); i++) {
        if (!m_neighbours[i].location->isOccupied() || m_neighbours[i].location->getCurrentPlayer()->isMrX()) {
            availableConnections.push_back(&m_neighbours[i]);
        }
    }
    return availableConnections;
}


const std::vector<Connection*> Location::getOccupiedConnections() {
    //returns vector with Connections
    std::vector<Connection*> occupiedConnections;

    //
    for (int i = 0; i < m_neighbours.size(); i++) {
        if (m_neighbours[i].location->isOccupied() && !(m_neighbours[i].location->getCurrentPlayer()->isMrX())) {
            //Tiles with Mr.X on them will not be added to this.
            occupiedConnections.push_back(&m_neighbours[i]);
        }
    }
    return occupiedConnections;
}


std::string Location::getName() {
    return m_name;
}


Player* Location::getCurrentPlayer() {
    return m_currentPlayer;
}


//
//-----setter-----
//
void Location::setName(std::string name) {
    m_name = name;
}

void Location::setCurrentPlayer(Player* currentPlayer) {
    //Adds pointer to player on this location
    m_currentPlayer = currentPlayer;
}

void Location::setStartingPosition() {
    m_isStartingPosition = true;
}