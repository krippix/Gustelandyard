#pragma once 
#include "game.hpp"

class Server {
private:
	//variables
	int m_sessionPin;
public:
	void startSession();
	void generatePin();
	
};