#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "location.hpp"
class Location;

class Player{
    private:
        Location* m_currentLocation = nullptr;
        bool m_isMrX = false;
        std::string m_name;
        std::vector<int> m_tickets {11,8,4,0,0}; //taxi,bus,bahn,black,doubleturn
        //0 - taxi, 1 -> bus, 2 -> train, 3 -> black, 4 -> double 
        std::vector<Location*> m_locationHistory;

    public:
        //constructor
        Player();
        
        //functions
        void create();
        void useTicket();
        void addTickets(std::vector<int>);
        
        //getter
        Location* getLocation() const;
        std::string getName() const;
        std::vector<int> getTickets();
        void printTickets() const;
        bool isMrX();
        
        //setter
        void setName(std::string);
        void setMrX();
        void setLocation(Location* newLocation);    
};