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

    std::cout << "enter name: ";
    std::cin >> name_tmp;
    setName(name_tmp);
}

void Player::addTickets(std::vector<int> newTickets) { //Adds tickets duh
    for (int i = 0; i < newTickets.size();i++) {
        m_tickets[i] += newTickets[i];
    }
}

//
//-----Getter-----
//
Location* Player::getLocation() const {
    return m_currentLocation;
}

std::string Player::getName() const {
    return Player::m_name;
}

std::vector<int> Player::getTickets() const {
    return Player::m_tickets;
}

void Player::printTickets() const {
    std::cout << "Tickets: " << std::endl;

    if (m_isMrX) {
        std::cout << "[black]: " << m_tickets[3] << "[2xTurn] : " << m_tickets[4];
    }
    else {
        std::cout << "[taxi]: " << m_tickets[0] << " [bus]: " << m_tickets[1] << " [train]: " << m_tickets[2];
    }
    std::cout << std::endl;
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

void Player::setLocation(Location* newLocation){
    //Pointer to new location set on player. Careful: Hast to be set on location itself aswell!
    m_currentLocation = newLocation;
}