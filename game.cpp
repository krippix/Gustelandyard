#include "game.hpp"

//Vector of player objects for current game
std::vector<player> players;
//Status of game
bool gameover = false;

game::game(){
    //Konstruktor
    std::cout << "Anzahl der Spieler: ";
    //2 to 6 players
    std::cin >> playercount;

    for(int i=0; i < playercount; i++){
        game::addPlayer(i);
    }


}
//
//-----Getter-----
//
bool game::getGameover(){
    return gameover;
}


void game::addPlayer(int i){
    //Creates new Player Object and adds it to the vector
    player player_tmp(i);
    players.push_back(player_tmp);
}

