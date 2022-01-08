#pragma once
#include <iostream>
#include <vector>

#include "player.hpp"

class game{
    private:
        //Zahl der Spieler
        std::vector<player> players;
        bool gameover;
        int playercount;
    public:
        
        //constructor
        game();
        //Spielerobjekte
        

        bool getGameover();
        void addPlayer(int);
        
};