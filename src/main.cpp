#include <thread>
#include <chrono>
#include "zmq.hpp"
#include "player.hpp"
#include "server.hpp"
#include "client.hpp"
#include "json.hpp"


int main() {
    
    // initialization
    zmq::context_t ctx{1};
    
    // constructs a reply socket and binds it
    zmq::socket_t socket{ ctx, zmq::socket_type::rep };
    socket.bind("tcp://*:5555");

    // prepare static data for responses
    const std::string data = "Coggers";
    /*
    while (true) {
        zmq::message_t request;

        //recieve request from client
        socket.recv(request, zmq::recv_flags::none);
        std::cout << "Poggies: " << request.to_string() << std::endl;

        //sleep
        std::this_thread::sleep_for(std::chrono::seconds(1));

        //send reply to client
        socket.send(zmq::buffer(data), zmq::send_flags::none);
    };
    */


    bool host;

    std::cout << "Do you want to join [0] or host [1] a game? ";
    std::cin >> host;
    
    if (host) {
        Server game;
        game.start();
    }
    else {
        //Client game;
        //game.join();
        //game.start();
    }

    
}