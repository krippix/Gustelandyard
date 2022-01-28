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
    }
    
    //Now adds edges between the connections, iterates through Connection Types
    for (int i = 0; i < locationsJ["edges"].size(); i++) {
        
        //Appends Pointer to connected Location to location
        for (int j = 0; j < locationsJ["edges"][i].size(); j++) {

            //Adds content of right side to left id side of the vector to 
            m_locations[locationsJ["edges"][i][j][0]].addNeighbour(i, &m_locations[locationsJ["edges"][i][j][1]]);

            
            //Now the same thing but sides are revesed
            m_locations[locationsJ["edges"][i][j][1]].addNeighbour(i, &m_locations[locationsJ["edges"][i][j][0]]);
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


//
//-----setter-----
//