#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "player.hpp"

class Player;
class Location;


struct Connection {
	int connectionType;
	Location* location;
};

class Location {
private:
	int m_index;
	std::string m_name;
	std::vector<Connection> m_neighbours; //Contains Connection Structure
	Player* m_currentPlayer = nullptr; //Player currently at the location
	bool m_isStartingPosition = false;
public:
	//constructor
	Location(int index,std::string name);
		
	//getter
	bool isStartingPosition() const;
	bool isOccupied() const; //Checks if player is at the location
	const std::vector<Connection*> getAllConnections();
	const std::vector<Connection*> getEmptyConnections();
	const std::vector<Connection*> getOccupiedConnections();
	std::string getName();
	Player* getCurrentPlayer();

	//function
	void addNeighbour(int type, Location* neighbourLocation);

	//setter
	void setName(std::string name);
	void setCurrentPlayer(Player* currentPlayer);
	void setStartingPosition();
};