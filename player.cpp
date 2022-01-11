#include "player.hpp"
//
//-----constructor-----
//
Player::Player(){
    //String name
    create();
};

//
//-----functions-----
//
void Player::create(){
    //Creates Player int of curren no.
    std::string name_tmp;

    std::cout << "Name des Spielers: ";
    std::cin >> name_tmp;
    setName(name_tmp);
}

void Player::addTickets(std::vector<int> newTickets){ //Adds tickets duh
    for (int i=0; i < newTickets.size() ;i++){
        m_tickets[i] += newTickets[i];
    }
}

//
//-----Getter-----
//
int Player::getPosition(){
    return Player::m_position;
}

std::string Player::getName(){
    return Player::m_name;
}

std::vector<int> Player::getTickets(){
    return Player::m_tickets;
}
//
//-----Setter-----
//
void Player::setName(std::string newname){
    //Sets name in player object
    Player::m_name = newname;
}

void Player::setMrX(){
    //makes Player Mr. X
    Player::m_isMrX = true;
    std::vector<int> xTickets {39,42,46,5,2}; //adds Tickets for Mr.X
    addTickets(xTickets);
}

void Player::setPosition(int newPosition){
    //Saves new Position to player object. But the movement has to be confirmed in map!!
    m_position = newPosition;
}