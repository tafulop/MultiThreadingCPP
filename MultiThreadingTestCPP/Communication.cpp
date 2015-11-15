#include "Communication.h"

Communication::Communication()
{
}

Communication::~Communication()
{
}

void Communication::setAngles(std::vector<float> angles)
{
	std::lock_guard<std::mutex> guard(mutex);

	this->angles = angles;
}

std::vector<float> Communication::getAngles()
{
	std::lock_guard<std::mutex> guard(mutex);
	return this->angles;
}



bool Communication::instanceFlag = false;
Communication* Communication::single = nullptr;


Communication * Communication::getInstance()
{
	if (Communication::instanceFlag == false) {
		single = new Communication();
		instanceFlag = true;
	}
	return single;
}