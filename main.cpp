#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "player.hpp"
#include "game.hpp"
#include "json.hpp"

using json = nlohmann::json;


int main(){

    Game currentsession;


    //incease turns until game is set to gameover
    do{
        currentsession.nextTurn();
    } while(currentsession.getGameover());

    

}

