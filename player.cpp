#include "player.hpp"

std::string name;

player::player(int currentNumber){
    //String name
    player::create(currentNumber);
};


void player::create(int currentNumber){
    //Creates Player int of curren no.
    std::string name_tmp;

    std::cout << "Namen des " << currentNumber + 1 << ". Spielers: ";
    std::cin >> name_tmp;
    player::setName(name_tmp);
}

//
//-----Getter-----
//




//
//-----Setter-----
//
void player::setName(std::string name_tmp){
    //Sets name in player object
    player::name = name_tmp;
}