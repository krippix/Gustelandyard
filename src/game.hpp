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
    int m_gamepin;
    int m_currentTurn = 0;
    bool m_gameover = false;
    bool m_isHost = false;

    //fuctions
    void chooseMrX();


public:
    //constructor

    //functions
    void start();
    void host();
    void join();
    void addPlayer(bool ownUser);
    void assignStartPositions();
    void nextTurn();
    void movePlayer(Player* currentPlayer);
    void announceMrXposition();
    int randomInteger(int x, int y);
    void generatePin();

    //getter
    bool getGameover();
    Player getPlayer(int);
    bool isEveryoneStuck();
    int getGamePIN();

    //setter
    void setHosted();
    void setPlayerCount();
    void setLocation(Player* currentPlayer, Location* newLocation);
};