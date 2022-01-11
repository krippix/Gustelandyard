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
        
    
    for (int i = 0; i < source["edges"].size();i++){
        result_vector.push_back(source["edges"][i]);
        
        for (int j = 0; j < source["edges"][i].size(); j++){
            result_vector[i].push_back(source["edges"][i][j]);
        } 
    }
    return result_vector;
}
//
//-----Getter-----
//
std::vector<int> Map::getStartingPositions(){
    return Map::m_edges[0][0];
}

//
//-----setter-----
//