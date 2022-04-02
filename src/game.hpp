#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include "player.hpp"
#include "map.hpp"
#include "network.hpp"

class Game {
private:
    //variables
    std::vector<Player> m_players; //Vector with player objects
    Map m_currentMap;
    int m_currentTurn = 0;
    bool m_gameover = false;
    bool m_isHost = false;

    //fuctions
    void chooseMrX();


public:
    // ---- constructor ----

    // ---- functions ----
    void prepare();

    // creates player object and adds it into m_players
    void addPlayer(std::string name);
    
    // calls addPlayer but asks for local userinput
    void addPlayerHost();
    void assignStartPositions();
    void nextTurn();
    void movePlayer(Player* currentPlayer);
    void announceMrXposition();
    static int randomInteger(int x, int y);

    // ---- getter ----
    bool getGameover();
    Player getPlayer(int);
    bool isEveryoneStuck();

    // ---- setter ----
    void setHosted();
    void setLocation(Player* currentPlayer, Location* newLocation);
};