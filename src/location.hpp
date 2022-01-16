#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "player.hpp"

class Player;
class Location;

enum class ConnectionType{taxi=0, bus=1, train=2, boat=3};

struct Connection {
	ConnectionType connectionType;
	Location* location;
};

class Location {
	private:
		int m_index;
		std::string m_name;
		std::vector<Connection> m_neighbours; //Contains Connection Structure 
		Player* m_currentPlayer; //Player currently at the location
		bool m_isStartingPosition = false;
	public:
		//constructor
		Location(int index,std::string name);
		
		//getter
		bool isStartingPosition() const;
		bool isOccupied() const; //Checks if player is at the location
		std::vector<Connection> getNeighbours() const;
		std::vector<Location*> getAvailableLocations() const;
		std::vector<Location*> getOccupiedLocations() const;

		//function
		void addNeighbour(ConnectionType type, Location* neighbourLocation);

		//setter
		void setName(std::string name);
		void setCurrentPlayer(const Player* currentPlayer);
		void setStartingPosition();
};