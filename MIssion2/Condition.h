#pragma once

#include "Type.h"
#include "PartPublisher.h"
#include "PartPublisherList.h"

class Condition
{
public:
	static bool isExit(std::string input);
	static bool isNumber(std::string input);
	static bool isValidCarType(int step, int answer, PartPubisherList publishers);
	static bool isValidEngineType(int step, int answer, PartPubisherList publishers);
	static bool isValidBrakeType(int step, int answer, PartPubisherList publishers);
	static bool isValidSteeringType(int step, int answer, PartPubisherList publishers);
	static bool isValidTestType(int step, int answer);
	static std::string findFaulty(PartPublisher* stack[10]);
	
};