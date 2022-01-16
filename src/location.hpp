#include <string>
#include <vector>

#include "player.hpp"
class Location;
enum class ConnectionType{taxi, bus, train, boat};

struct Connection {
	ConnectionType connectionType;
	const Location* location;
};

class Location {
	private:
		int m_index;
		std::string m_name;
		std::vector<Connection> m_connections; //Contains Connection Structure 
		const Player* m_currentPlayer; //Player currently at the location
		bool m_isStartingPosition = false;
	public:
		//constructor
		Location(int index,std::string name);
		
		//getter

		//function
		void addNeighbour(ConnectionType type, Location* neighbourLocation);

		//setter
		void setName(std::string name);
		void setCurrentPlayer(const Player* currentPlayer);
		void setStartingPosition();
};