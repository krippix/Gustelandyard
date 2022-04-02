#include <thread>
#include <chrono>
#include "zmq.hpp"
#include "player.hpp"
#include "server.hpp"
#include "client.hpp"
#include "json.hpp"


int main() {

    std::cout << "   _____           _       _                 _                     _ " << std::endl;
    std::cout << "  / ____|         | |     | |               | |                   | |" << std::endl;
    std::cout << " | |  __ _   _ ___| |_ ___| | __ _ _ __   __| |_   _  __ _ _ __ __| |" << std::endl;
    std::cout << " | | |_ | | | / __| __/ _ \\ |/ _` | '_ \\ / _` | | | |/ _` | '__/ _` |" << std::endl;
    std::cout << " | |__| | |_| \\__ \\ ||  __/ | (_| | | | | (_| | |_| | (_| | | | (_| |" << std::endl;
    std::cout << "  \\_____|\\__,_|___/\\__\\___|_|\\__,_|_| |_|\\__,_|\\__, |\\__,_|_|  \\__,_|" << std::endl;
    std::cout << "                                                __/ |                " << std::endl;
    std::cout << "                                               |___/                 " << std::endl << std::endl;

    //Decide wheather to host or join game
    bool valid = true;
    bool mode;
    std::cout << "Do you want to host [0] or join [1] a game? ";
    std::string input;
    do {
        std::cin >> input;

        if (input == "0") {
            mode = 0;
        }
        else if (input == "1") {
            mode = 1;
        }
        else {
            valid = false;
        }
        if (!(input == "0") && !(input == "1")) {
            std::cout << "Your input is invalid, please try again: ";
        }
    } while (!valid);

    //start session as host/client
    if (mode == 0) {
        Server server;
        server.startSession();
    }

    if (mode == 1) {
        Client game;
        game.join();
    }
}