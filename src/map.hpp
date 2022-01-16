#pragma once
#include <iostream>
#include <fstream>

#include "location.hpp"
#include "player.hpp"
#include "json.hpp"
using json = nlohmann::json;

class Map{
    private:
        std::string m_name = "Sigmaringen"; //Name of the Map, TODO: Make non-static
        std::vector<Location> m_locations;
        //0 startloc.,1 taxi, 2 bus, 3 train, 4 boat
        std::vector<std::vector<std::vector<int>>> m_edges; // m_edges[vehicle_type][no.][edge(0 or 1)]
        
        //setter

    public:
        //constructor
        Map();
        
        //functions
        void parseMapData();
        std::vector<std::vector<std::vector<int>>> convertEdgesToVector(json&);

        //getter
        std::vector<int> getStartingPositions();
        std::vector<std::vector<int>> getAvailableEdges(int);
        std::string getLocationName(int);
        std::vector<std::vector<int>> getLegalMoves(std::vector<Player>, Player);
        
        //setter
        
        
       
        


};