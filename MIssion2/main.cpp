#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

#include "Type.h"
#include "PartPublisher.h"
#include "PartPublisherList.h"
#include "Condition.h"
#include "Util.h"

#define CLEAR_SCREEN "\033[H\033[2J"

void runProducedCar();
void testProducedCar();
void delay(int ms);

void displayMenu(int step, PartPubisherList publishers);
bool checkPart(int step, int answer, PartPubisherList publishers);
bool checkStep(int& step, int answer);
void processPartsSelctionStep(int step, int answer, PartPubisherList publishers);
void processRunStep(int answer);
void nextStep(int& step, int answer, PartPubisherList publishers);

PartPublisher* stack[10];

void delay(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

class Screen
{
public:
	static std::string getInput()
	{
		std::string input;
		std::cout << "INPUT > ";
		std::cin >> input;

		return input;
	}
};

int main()
{
	int step = CarType_Q;
	PartPubisherList publishers;

	while (true)
	{
		displayMenu(step, publishers);

		std::string input = Screen::getInput();
		Util::trimNewlineChar(input);

		if (Condition::isExit(input))
		{
			std::cout << "���̹���\n";
			break;
		}
		if (Condition::isNumber(input) == false)
		{
			std::cout << "ERROR :: ���ڸ� �Է� ����\n";
			delay(800);
			continue;
		}

		int answer = Util::getNumebr(input);

		if (checkPart(step, answer, publishers))
		{
			continue;
		}
		else if (checkStep(step, answer))
		{
			continue;
		}

		nextStep(step, answer, publishers);
	}
}

void runProducedCar()
{
	if (Condition::findFaulty(stack).size() > 0)
	{
		std::cout << "�ڵ����� ���۵��� �ʽ��ϴ�\n";
		return;
	}
	if (stack[Engine_Q]->getNameUppercase() == "BROKEN")
	{
		std::cout << "������ ���峪�ֽ��ϴ�.\n";
		std::cout << "�ڵ����� �������� �ʽ��ϴ�.\n";
		return;
	}

	std::cout << "Car Type : " + stack[CarType_Q]->getName() + "\n";
	std::cout << "Engine : " + stack[Engine_Q]->getName() + "\n";
	std::cout << "Brake System : " + stack[brakeSystem_Q]->getName() + "\n";
	std::cout << "Steering System : " + stack[SteeringSystem_Q]->getName() + "\n";

	std::cout << "�ڵ����� ���۵˴ϴ�.\n";
}

void testProducedCar()
{
	std::string failReason = "";
	std::string failMessage = "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : FAIL\n";
	std::string successMessage = "�ڵ��� ��ǰ ���� �׽�Ʈ ��� : PASS\n";

	// ���ռ��� �´��� Ȯ��
	failReason = Condition::findFaulty(stack);

	// ���ռ��� ���� ��� ���
	if (failReason.size() > 0)
	{
		std::cout << failMessage;
		std::cout << failReason;
	}
	else
	{
		std::cout << successMessage;
	}
}

void displayMenu(int step, PartPubisherList publishers)
{
	std::cout << CLEAR_SCREEN;

	int number = 1;
	switch (step)
	{
	case CarType_Q:
		std::cout << "        ______________\n";
		std::cout << "       /|            | \n";
		std::cout << "  ____/_|_____________|____\n";
		std::cout << " |                      O  |\n";
		std::cout << " '-(@)----------------(@)--'\n";
		std::cout << "===============================\n";
		std::cout << "� ���� Ÿ���� �����ұ��?\n";
		std::cout << publishers.getCarFabs();

		break;

	case Engine_Q:
		std::cout << "� ������ ž���ұ��?\n";
		std::cout << "0. �ڷΰ���\n";
		std::cout << publishers.getEngineFabs();

		break;

	case brakeSystem_Q:
		std::cout << "� ������ġ�� �����ұ��?\n";
		std::cout << "0. �ڷΰ���\n";
		std::cout << publishers.getBrakeFabs();

		break;

	case SteeringSystem_Q:
		std::cout << "� ������ġ�� �����ұ��?\n";
		std::cout << "0. �ڷΰ���\n";
		std::cout << publishers.getSteeringFabs();

		break;

	case Run_Test:
		std::cout << "���� ������ �ϼ��Ǿ����ϴ�.\n";
		std::cout << "� ������ �ұ��?\n";
		std::cout << "0. ó�� ȭ������ ���ư���\n";
		std::cout << "1. RUN\n";
		std::cout << "2. Test\n";

		break;
	}
	std::cout << "===============================\n";
}

bool checkPart(int step, int answer, PartPubisherList publishers)
{
	std::string failReason = "";

	// ���ռ� Ȯ��
	if (Condition::isValidCarType(step, answer, publishers))
	{
		failReason = "ERROR :: ���� Ÿ���� 1 ~ 3 ������ ���� ����\n";
	}
	else if (Condition::isValidEngineType(step, answer, publishers))
	{
		failReason = "ERROR :: ������ 1 ~ 4 ������ ���� ����\n";
	}
	else if (Condition::isValidBrakeType(step, answer, publishers))
	{
		failReason = "ERROR :: ������ġ�� 1 ~ 3 ������ ���� ����\n";
	}
	else if (Condition::isValidSteeringType(step, answer, publishers))
	{
		failReason = "ERROR :: ������ġ�� 1 ~ 2 ������ ���� ����\n";
	}
	else if (Condition::isValidTestType(step, answer))
	{
		failReason = "ERROR :: Run �Ǵ� Test �� �ϳ��� ���� �ʿ�\n";
	}

	// ���ռ��� ���� ��� ���
	if (failReason.size() > 0)
	{
		std::cout << failReason;
		delay(800);
		return true;
	}
	else
	{
		return false;
	}
}

bool checkStep(int& step, int answer)
{
	if (answer > 0) return false;


	if (step == Run_Test)
	{
		step = CarType_Q;
	}
	if (step >= 1)
	{
		step -= 1;
	}

	return true;
}

void processPartsSelctionStep(int step, int answer, PartPubisherList publishers)
{
	switch (step)
	{
	case CarType_Q:
		stack[CarType_Q] = publishers.findCarFabs(answer);
		std::cout<<stack[CarType_Q]->getCar();
		break;
	case Engine_Q:
		stack[Engine_Q] = publishers.findEngineFabs(answer);
		std::cout << stack[Engine_Q]->getEngine();
		break;
	case brakeSystem_Q:
		stack[brakeSystem_Q] = publishers.findBrakFabs(answer);
		std::cout << stack[brakeSystem_Q]->getBrake();
		break;
	case SteeringSystem_Q:
		stack[SteeringSystem_Q] = publishers.findSteeringFabs(answer);
		std::cout << stack[SteeringSystem_Q]->getSteering();
		break;
	default:
		break;
	}
}

void processRunStep(int answer)
{
	switch (answer)
	{
	case 1:
		runProducedCar();
		break;
	case 2:
		std::cout << "Test...\n";
		delay(1500);
		testProducedCar();
		break;
	default:
		break;
	}
}

void nextStep(int& step, int answer, PartPubisherList publishers)
{
	if (step <= SteeringSystem_Q)
	{
		processPartsSelctionStep(step, answer, publishers);
		delay(800);
		step++;
	}
	else
	{
		processRunStep(answer);
		delay(2000);
	}
}

 #endif