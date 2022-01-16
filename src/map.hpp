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
        
        //setter

    public:
        //constructor
        Map();
        
        //functions
        void parseMapData();

        //getter
        std::vector<Location*> getStartingLocations();
        std::vector<std::vector<Location*>> getMoves(Player* currentPlayer) const;
        
        //setter
        
        
       
        


};