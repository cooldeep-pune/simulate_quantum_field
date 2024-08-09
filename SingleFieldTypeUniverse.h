#ifndef SINGLEFIELDTYPEUNIVERSE_H
#define SINGLEFIELDTYPEUNIVERSE_H
#include <mutex>
#include <mem.h>
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include "Universal.h"
#include "UniverseField.h"
#include "UniverseInterface.h"

class SingleFieldTypeUniverse : public UniverseInterface
{
private:

public:
	SingleFieldTypeUniverse(const SingleFieldTypeUniverse&) = delete;
    SingleFieldTypeUniverse& operator=(const SingleFieldTypeUniverse&) = delete;
    static SingleFieldTypeUniverse* instance() {
    	std::lock_guard<std::mutex> lck(m_singletonMutex);
	    if (!instance_) {
	      instance_ = new SingleFieldTypeUniverse();
	    }
	     return instance_;
   }
	virtual void InitializeUniverse();
	virtual void SimulateUniverse();
	virtual void Display();
	virtual void SaveToFile();
	void ClearScreen();
	static void InAction(int energyboost);
	static void LayeredAction(int energyboost);
	static void GodThread();
private:
  	SingleFieldTypeUniverse() { }
	static SingleFieldTypeUniverse* instance_;
	static std::mutex m_singletonMutex;
	static std::mutex glock;
	static UField m_space[SPACE][SPACE][SPACE];
};
#endif