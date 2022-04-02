#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "location.hpp"
class Location;
struct Connection;

class Player{
private:
    // Player ID to for online usage
    std::string m_onlineId; 

    // Player name
    std::string m_name;

    // location object containing current location (:P)
    Location* m_currentLocation = nullptr;

    // Player tickets: cab, bus, train, black, doubleturn
    std::vector<int> m_tickets{ 11,8,4,0,0 };

    // history of turns to allow "replay" at the end
    std::vector<Location*> m_locationHistory;
    
    // wheather player is mr.x
    bool m_isMrX = false;

    // sets player as permanently stuck - can no longer move
    bool m_isPermStuck = false;

    // marks player as possibly stuck in order to check from another perspective
    bool m_possiblyStuck = false; //Used to determine if neighbour is stuck
    
    //True while Mr.X is using 2x Ticket
    bool m_activeDoubleMove = false; 

public:
    // ---- constructor ----
    Player(std::string name);
        
    //functions
    void useTicket(int locationType);
    void addTickets(std::vector<int>);
        
    //getter
    std::string getOnlineId();
    Location* getLocation() const;
    std::string getName() const;
    std::vector<int> getTickets();
    void printTickets() const;
    bool isMrX();
    bool isPermStuck();
    void printMoves(Player* currentPlayer, std::vector<std::vector<Connection*>> allConnections);
    bool isMrX_isTrapped();
    std::vector<std::vector<Connection*>> getMoves();
    int Player::getHistorySize();
    bool getActiveDoubleMove();

    //setter
    void setName(std::string);
    void setMrX();
    void setLocation(Location* newLocation);    
    void setPermStuck();
    void setActiveDoubleMove(bool status);
};