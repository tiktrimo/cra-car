#pragma once
#include <string>
#include <vector>

class PartPublisher
{
public:
	std::string name = "Default_Name_placeholder";
	bool isCarFab = false;
	bool isEngineFab = false;
	bool isBrakeFab = false;
	bool isSteeringFab = false;

	virtual std::string getName();
	virtual std::string getNameUppercase();

	virtual std::string getCar();
	virtual std::string getEngine();
	virtual std::string getBrake();
	virtual std::string getSteering();

};

