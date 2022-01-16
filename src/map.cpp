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
    for (int i = 0; i < locationsJ["edges"]["startingPositions"][i]; i++) {
        //Mark starting Positions in location objects
        m_locations[i].setStartingPosition();
    }
    
    //Now adds edges between the connections
    for (int i=0; i < locationsJ["edges"])

        --> CONTINUE HERE!!//Try to interpret enum ConnectionType as String to pull it from the json file
    
}

std::vector<std::vector<std::vector<int>>> Map::convertEdgesToVector(json& source){
    std::vector<std::vector<std::vector<int>>> result_vector;
        
    
    for (int i = 0; i < source["edges"].size(); i++){
        result_vector.push_back(source["edges"][i]);
    }
    return result_vector;
}
//
//-----Getter-----
//

/* Im Locations Objekt implementieren
std::vector<int> Map::getStartingPositions(){
    return Map::m_edges[0][0];
}
*/

/* Im locations objekt implementieren
std::vector<std::vector<int>> Map::getAvailableEdges(int currentPosition){
    //Search map for Edges with current Position
    std::vector<std::vector<int>> result_edges {{},{},{},{}};

    //returns ve

    //iterates through all edges
    for (int i=1; i < m_edges.size(); i++){ //starting at 1 because 0 contains the starting positions

        for (int j=0; j < m_edges[i].size(); j++){
            
            //[edge no.]
            //std::cout << "Pos. " << currentPosition <<  "[" << m_edges[i][j][0] << "," << m_edges[i][j][1] << "]" <<std::endl;
            
            //left edge
            if (m_edges[i][j][0] == currentPosition){
                result_edges[i-1].push_back(m_edges[i][j][1]);
            }
            if (m_edges[i][j][1] == currentPosition){
                result_edges[i-1].push_back(m_edges[i][j][0]);
            }            
        }
    }

    return result_edges;
}
*/

std::string Map::getLocationName(int index) {
    //Returns name of location as string
    return m_locations[index];
}

std::vector<std::vector<int>> Map::getLegalMoves(std::vector<Player> players, Player currentPlayer) {
    //Takes Players and current Player as input and returns Vector of allowed Moves of the map

    std::vector<std::vector<int>> availableEdges = getAvailableEdges(currentPlayer.getPosition());

    //Remove occupied 
}

//
//-----setter-----
//