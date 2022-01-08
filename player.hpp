#pragma once
#include <iostream>
#include <vector>
#include <string>

class player{
    private:
        int position;
        std::string name;
        bool istMrX;
        std::vector<std::vector<int>> tickets;
        //0 - taxi, 1 -> bus, 2 -> train, 3 -> black, 4 -> double 

    public:
        //constructor
        player(int);
        void create(int);

        int getPosition();
        std::vector<std::vector<int>> getTickets();
        
        void setPosition(int);
        void setName(std::string);
        
        
        bool useTicket();


};