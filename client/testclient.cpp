#include <iostream>
#include <string>
#include "zmq.hpp"

int main() {
	//This client ist supposed to test the socket connection to the server
	//I think later clients will include it in the main application as a choice
	std::cout << "Damn son, thats a client" << std::endl;

	//initialize zmq context
	zmq::context_t context{1};

	// construct a request
	zmq::socket_t socket{ context, zmq::socket_type::req };
	socket.connect("tcp://localhost:5555");

	// set up some static data
	std::string data;

	for (auto request_num = 0; request_num < 10; ++request_num) {
		
		std::cin >> data;
		
		//send the message
		std::cout << "Sending Hello there" << request_num << "..." << std::endl;
		socket.send(zmq::buffer(data), zmq::send_flags::none);

		// wait for server reply
		zmq::message_t reply{};
		socket.recv(reply, zmq::recv_flags::none);

		std::cout << "Received " << reply.to_string();
		std::cout << " (" << request_num << ")";
		std::cout << std::endl;
		
		std::cin.clear();
	}
}