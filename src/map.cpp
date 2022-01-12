#include "map.hpp"

Map::Map(){
    parseMapData();
}
//
//-----functions-----
//
void Map::parseMapData(){
    
    std::ifstream mapdata;
    mapdata.open("data/maps/Sigmaringen/locations.json");
    

    json j = json::parse(mapdata);
    
    //Adds locations to vector from json file
    for (int i = 0; i < j["locations"].size();i++){
        m_locations.push_back(j["locations"][i]);
    }

      
    
    m_edges = convertEdgesToVector(j);

    //Auswahl aus den Im Ordner verfügbaren Maps erstellen
    //Bis dahin ist das hier eine Konstante.
    
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
std::vector<int> Map::getStartingPositions(){
    return Map::m_edges[0][0];
}

std::vector<std::vector<int>> Map::getEdges(int currentPosition){
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

//
//-----setter-----
//