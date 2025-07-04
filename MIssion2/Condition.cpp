#include "Condition.h"
#include "PartPublisherList.h"

bool Condition::isExit(std::string input)
{
	return input == "exit";
}

bool Condition::isNumber(std::string input)
{
	std::string::const_iterator it = input.begin();
	while (it != input.end() && std::isdigit(*it)) ++it;
	return !input.empty() && it == input.end();
}

bool Condition::isValidCarType(int step, int answer, PartPubisherList publishers)
{
	return step == CarType_Q && !(answer >= 1 && answer < publishers.getCarFabsCnt());
}

bool Condition::isValidEngineType(int step, int answer, PartPubisherList publishers)
{
	return step == Engine_Q && !(answer >= 0 && answer < publishers.getEngineFabsCnt());
}

bool Condition::isValidBrakeType(int step, int answer, PartPubisherList publishers)
{
	return step == brakeSystem_Q && !(answer >= 0 && answer < publishers.getBrakeFabsCnt());
}

bool Condition::isValidSteeringType(int step, int answer, PartPubisherList publishers)
{
	return step == SteeringSystem_Q && !(answer >= 0 && answer < publishers.getSteeringFabsCnt());
}

bool Condition::isValidTestType(int step, int answer)
{
	return step == Run_Test && !(answer >= 0 && answer <= 2);
}

std::string Condition::findFaulty(PartPublisher* stack[10])
{
	if (stack[CarType_Q]->getNameUppercase() == "SEDAN" && stack[brakeSystem_Q]->getNameUppercase() == "CONTINENTAL")
		return "Sedan에는 Continental제동장치 사용 불가\n";
	else if (stack[CarType_Q]->getNameUppercase() == "SUV" && stack[Engine_Q]->getNameUppercase() == "TOYOTA")
		return "SUV에는 TOYOTA엔진 사용 불가\n";
	else if (stack[CarType_Q]->getNameUppercase() == "TRUCK" && stack[Engine_Q]->getNameUppercase() == "WIA")
		return "Truck에는 WIA엔진 사용 불가\n";
	else if (stack[CarType_Q]->getNameUppercase() == "TRUCK" && stack[brakeSystem_Q]->getNameUppercase() == "MANDO")
		return "Truck에는 Mando제동장치 사용 불가\n";
	else if (stack[brakeSystem_Q]->getNameUppercase() == "BOSCH" && stack[SteeringSystem_Q]->getNameUppercase() != "BOSCH")
		return "Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n";

	return "";
}
