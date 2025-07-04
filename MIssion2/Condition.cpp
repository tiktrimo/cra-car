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
		return "Sedan���� Continental������ġ ��� �Ұ�\n";
	else if (stack[CarType_Q]->getNameUppercase() == "SUV" && stack[Engine_Q]->getNameUppercase() == "TOYOTA")
		return "SUV���� TOYOTA���� ��� �Ұ�\n";
	else if (stack[CarType_Q]->getNameUppercase() == "TRUCK" && stack[Engine_Q]->getNameUppercase() == "WIA")
		return "Truck���� WIA���� ��� �Ұ�\n";
	else if (stack[CarType_Q]->getNameUppercase() == "TRUCK" && stack[brakeSystem_Q]->getNameUppercase() == "MANDO")
		return "Truck���� Mando������ġ ��� �Ұ�\n";
	else if (stack[brakeSystem_Q]->getNameUppercase() == "BOSCH" && stack[SteeringSystem_Q]->getNameUppercase() != "BOSCH")
		return "Bosch������ġ���� Bosch������ġ �̿� ��� �Ұ�\n";

	return "";
}
