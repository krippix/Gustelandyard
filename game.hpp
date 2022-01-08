#pragma once
#include <iostream>
#include <vector>

#include "player.hpp"
#include "map.hpp"

class Game{
    private:
        //Zahl der Spieler
        std::vector<Player> players;
        bool m_gameover = false;
        int chooseMrX();
        Map currentMap;

    public:
        //constructor
        Game();

        //functions
        void addPlayer();

        //getter
        bool getGameover();
        Player getPlayer(int);
        

        //setter
        
        
};