#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "location.hpp"
class Location;
struct Connection;

class Player{
    private:
        Location* m_currentLocation = nullptr;
        bool m_isMrX = false;
        bool m_isPermStuck = false; //true once player cant move with their tickets
        bool m_possiblyStuck = false; //Used to determine if neighbour is stuck
        std::string m_name;
        std::vector<int> m_tickets {11,8,4,0,0}; //taxi,bus,bahn,black,doubleturn
        //0 - taxi, 1 -> bus, 2 -> train, 3 -> black, 4 -> double 
        std::vector<Location*> m_locationHistory;

    public:
        //constructor
        Player();
        
        //functions
        void create();
        void useTicket(int locationType);
        void addTickets(std::vector<int>);
        
        //getter
        Location* getLocation() const;
        std::string getName() const;
        std::vector<int> getTickets();
        void printTickets() const;
        bool isMrX();
        bool isPermStuck();
        void printMoves(Player* currentPlayer, std::vector<std::vector<Connection*>> allConnections);
        bool isMrX_isTrapped();
        std::vector<std::vector<Connection*>> getMoves();

        //setter
        void setName(std::string);
        void setMrX();
        void setLocation(Location* newLocation);    
        void setPermStuck();
};