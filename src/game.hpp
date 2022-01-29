#pragma once
#include <iostream>
#include "player.hpp"
#include "map.hpp"

class Game{
    private:
        //variables
        std::vector<Player> m_players; //Vector with player objects
        Map m_currentMap;
        int m_currentTurn = 0;
        bool m_gameover = false;
        
        //fuctions
        void chooseMrX();
        

    public:
        //constructor
        Game();

        //functions
        void addPlayer();
        void assignStartPositions();
        void nextTurn();
        void movePlayer(Player* currentPlayer);
        void announceMrXposition();

        //getter
        bool getGameover();
        Player getPlayer(int);
        bool isEveryoneStuck();

        //setter
        void setPlayerCount();
        void setLocation(Player* currentPlayer, Location* newLocation);
};