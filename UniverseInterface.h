#ifndef UNIVERSEINTERFACE_H
#define UNIVERSEINTERFACE_H

class UniverseInterface 
{
public:
	virtual void InitializeUniverse()=0;
	virtual void SimulateUniverse()=0;
	virtual void Display()=0;
};

#endif