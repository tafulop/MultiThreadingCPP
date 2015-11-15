#pragma once

#include <mutex>
#include <vector>

class Communication
{

private:
	std::mutex mutex;
	static Communication* single;
	static bool instanceFlag;
	Communication();

	
	std::vector<float> angles;

public:
	static Communication* getInstance();
	~Communication();

	void setAngles(std::vector<float> angles);
	std::vector<float> getAngles();

};

