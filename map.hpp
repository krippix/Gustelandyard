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
        //0 taxi, 1 bus, 2 train, 3 boat
        std::vector<std::vector<std::vector<int>>> m_edges; // m_edges[vehicle_type][no.][edge(0 or 1)] 
        
        //setter

    public:
        //constructor
        Map();
        
        //functions
        void parseMapData();
        std::vector<std::vector<int>> convertEdgesToVector(json&);

        //getter
        
        
        //setter
        
        
       
        


};