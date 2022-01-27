#include "player.hpp"
#include "game.hpp"
#include "json.hpp"



int main() {


    Game currentsession;

    //incease turns until game is set to gameover
    while (!currentsession.getGameover()) {
        currentsession.nextTurn();
    }
        
}

