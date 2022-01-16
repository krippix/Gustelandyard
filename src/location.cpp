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
	m_connections.push_back({ type,location });
}


//
//-----getter-----
//



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