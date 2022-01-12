#pragma once
#include <iostream>
#include <vector>
#include <string>

class Player{
    private:
        int m_position;
        bool m_isMrX;
        std::string m_name;
        std::vector<int> m_tickets {11,8,4,0,0}; //taxi,bus,bahn,black,doubleturn
        //0 - taxi, 1 -> bus, 2 -> train, 3 -> black, 4 -> double 

    public:
        //constructor
        Player();
        
        //functions
        void create();
        bool useTicket();
        void addTickets(std::vector<int>);
        
        //getter
        int getPosition();
        std::string getName();
        std::vector<int> getTickets();
        
        //setter
        void setName(std::string);
        void setMrX();
        void setPosition(int);
       
        


};