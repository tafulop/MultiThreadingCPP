#pragma once

#include <iostream>
#include <thread>
#include <stdio.h>
#include <zmq.h>
#include <string>
#include "Communication.h"

class Simulation
{
private: 
	std::string socketIP = "valami";
	int port = 5556;

	int sendDelay = 1000;

	// ZMQ Socket
	void *context;
	void *publisher;

	int rc;

	// singleton
	static bool intanceFlag;
	static Simulation* single;

	// motors
	// motors
	std::vector<char*> motors;


	Communication* c;

	std::thread communicator;

	void static Communicate();

	

public:
	Simulation();
	~Simulation();
	void startSend();
	static Simulation* getInstance();
};

