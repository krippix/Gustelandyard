#include "map.hpp"

Map::Map(){
    parseMapData();
}
//
//-----functions-----
//
void Map::parseMapData(){
    std::ifstream mapdata;
    mapdata.open("data/maps/"+m_name+"/locations.json");
    
    json locationsJ = json::parse(mapdata);

    //Creates Location Objects and appends Name and ID, NO EDGES ARE HERE YET!
    for (int i = 0; i < locationsJ["locations"].size(); i++) {
        
        Location currentLocation(i, locationsJ["locations"][i]);
        m_locations.push_back(currentLocation);
    }

    //Add starting Positions
    for (int i = 0; i < locationsJ["startingPositions"].size(); i++) {
        //Mark starting Positions in location objects
        m_locations[locationsJ["startingPositions"][i]].setStartingPosition();
        std::cout << "i: " << m_locations[locationsJ["startingPositions"][i]].isStartingPosition() << std::endl;
    }
    
    //Now adds edges between the connections, iterates through Connection Types
    for (int i = 0; i < locationsJ["edges"].size(); i++) {
        
        //Appends Pointer to connected Location to location
        for (int j = 0; j < locationsJ["edges"][i].size(); j++) {

            ConnectionType type; //Enum with vehicle type
            
            //Picks type to append
            switch (i) {
                case 0: type = ConnectionType::taxi;
                    break;
                case 1: type = ConnectionType::bus;
                    break;
                case 2: type = ConnectionType::train;
                    break;
                case 3: type = ConnectionType::boat;
                    break;
            }

            //Adds content of right side to left id side of the vector to 
            m_locations[locationsJ["edges"][i][j][0]].addNeighbour(type, &m_locations[locationsJ["edges"][i][j][1]]);

            std::cout << "Edges: [" << locationsJ["edges"][i][j][0] << "," << locationsJ["edges"][i][j][1] << std::endl;
            
            //Now the same thing but sides are revesed
            m_locations[locationsJ["edges"][i][j][1]].addNeighbour(type, &m_locations[locationsJ["edges"][i][j][0]]);
        }
    }

        
    
}

//
//-----Getter-----
//


std::vector<Location*> Map::getStartingLocations() {
    //Returns vector of pointers to possible starting locations
    std::vector<Location*> startingPositions;

    for (int i = 0; i < m_locations.size(); i++) {
        if (m_locations[i].isStartingPosition()) {
            startingPositions.push_back(&m_locations[i]);
        }
    }
    return startingPositions;
}

/* I think this should be implemented in GAME.cpp
std::vector<std::vector<Location*>> Map::getMoves(Player* currentPlayer) const {
    //Input Player pointer, returns vector of locations [0]-> occupied, [1]-> possible
    std::vector<std::vector<Location*>> moves;
    
    currentPlayer->getPosition()->getOccupiedLocations();

    //Remove occupied 

    return moves;
}
*/

//
//-----setter-----
//