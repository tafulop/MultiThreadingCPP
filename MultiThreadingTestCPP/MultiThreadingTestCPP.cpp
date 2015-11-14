// MultiThreadingTestCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <thread>
#include <iostream>
#include <mutex>


struct Counter {
	int value;
	std::mutex mutex;
	float angles[5] = { 0 };

	Counter() : value(0) {}


	void setAngles(float *p) {
		
		int size = sizeof(*p);

		std::lock_guard<std::mutex> guard(mutex);

		for (int i = 0; i <= size; i++) {
			
			angles[i] = *p++;
		}
	}

	void printAngles() {

		std::lock_guard<std::mutex> guard(mutex);

		for (int i = 0; i < 5; i++) {

			std::cout << "Angle " << i << " " << angles[i] << std::endl;
		}
	
	}


	void increment() {
		std::lock_guard<std::mutex> guard(mutex);
		++value;
	}
};

int main()
{

	Counter counter;

	std::vector<std::thread> threads;

	for (int i = 0; i < 5; ++i) {
		threads.push_back(std::thread([&counter]() {
			for (int i = 0; i < 100; ++i) {
				if (i % 2) {
					float angs[5] = { 123.1 + i, 123.2 + i , 123.3 + i, 124.4 + i , 123.5 +i   };
					counter.setAngles(angs);
				}
				else {
					counter.printAngles();
				}
				counter.increment();
			}
		}));
	}

	for (auto& thread : threads) {
		thread.join();
	}

	std::cout << counter.value << std::endl;

	system("pause");

	return 0;
	
}

