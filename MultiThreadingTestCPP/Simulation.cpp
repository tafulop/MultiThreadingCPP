#include "Simulation.h"

typedef void(Simulation::*CommPtr)();

Simulation::Simulation()
{
	// Init socket
	context = zmq_ctx_new();
	publisher = zmq_socket(context, ZMQ_PUB);
	rc = zmq_bind(publisher, "tcp://*:5556");
	
	// Add motor names to the container
	motors.push_back("M1");
	motors.push_back("M2");
	motors.push_back("M3");
	motors.push_back("M4");
	motors.push_back("M5");

	this->c = Communication::getInstance();
}


Simulation::~Simulation()
{
	this->communicator.~thread();
}


void Simulation::Communicate()
{

	std::vector<float> angs;
	std::vector<char*> motors = Simulation::getInstance()->motors;
	int delayTime = Simulation::getInstance()->sendDelay;

	void* pub = Simulation::getInstance()->publisher;
	
	while (1) {

		angs = Communication::getInstance()->getAngles();
		zmq_msg_t message;
		zmq_msg_init_size(&message, 20);

		// send angle values
		for (int i = 0; i < angs.size(); i++) {
			snprintf((char*)zmq_msg_data(&message), 20, "%s %f", motors[i], angs[i]);
			zmq_send(pub, &message, 15, 0);
			std::cout << "Sent message: " << i << std::endl;
		}

		Sleep(delayTime);
	}

}

void Simulation::startSend()
{
	this->communicator = std::thread(&this->Communicate);
}


bool Simulation::intanceFlag = false;
Simulation* Simulation::single = nullptr;


Simulation * Simulation::getInstance()
{
	if (Simulation::intanceFlag == false)
	{
		Simulation::single = new Simulation();
		Simulation::intanceFlag = true;
	}

	return single;
}
