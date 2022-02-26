#pragma once
#include "player.hpp"

class Network {
private:

public:
	//functions
	void establishConnection();
	Player awaitPlayers();
};