#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "json.hpp"
using json = nlohmann::json;

class Map{
    private:
        std::string m_name; //Name of the Map
        std::vector<std::string> m_locations;
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
        
        //setter
        
        
       
        


};