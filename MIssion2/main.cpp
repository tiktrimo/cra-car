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
			std::cout << "바이바이\n";
			break;
		}
		if (Condition::isNumber(input) == false)
		{
			std::cout << "ERROR :: 숫자만 입력 가능\n";
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
		std::cout << "자동차가 동작되지 않습니다\n";
		return;
	}
	if (stack[Engine_Q]->getNameUppercase() == "BROKEN")
	{
		std::cout << "엔진이 고장나있습니다.\n";
		std::cout << "자동차가 움직이지 않습니다.\n";
		return;
	}

	std::cout << "Car Type : " + stack[CarType_Q]->getName() + "\n";
	std::cout << "Engine : " + stack[Engine_Q]->getName() + "\n";
	std::cout << "Brake System : " + stack[brakeSystem_Q]->getName() + "\n";
	std::cout << "Steering System : " + stack[SteeringSystem_Q]->getName() + "\n";

	std::cout << "자동차가 동작됩니다.\n";
}

void testProducedCar()
{
	std::string failReason = "";
	std::string failMessage = "자동차 부품 조합 테스트 결과 : FAIL\n";
	std::string successMessage = "자동차 부품 조합 테스트 결과 : PASS\n";

	// 정합성이 맞는지 확인
	failReason = Condition::findFaulty(stack);

	// 정합성에 따라 결과 출력
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
		std::cout << "어떤 차량 타입을 선택할까요?\n";
		std::cout << publishers.getCarFabs();

		break;

	case Engine_Q:
		std::cout << "어떤 엔진을 탑재할까요?\n";
		std::cout << "0. 뒤로가기\n";
		std::cout << publishers.getEngineFabs();

		break;

	case brakeSystem_Q:
		std::cout << "어떤 제동장치를 선택할까요?\n";
		std::cout << "0. 뒤로가기\n";
		std::cout << publishers.getBrakeFabs();

		break;

	case SteeringSystem_Q:
		std::cout << "어떤 조향장치를 선택할까요?\n";
		std::cout << "0. 뒤로가기\n";
		std::cout << publishers.getSteeringFabs();

		break;

	case Run_Test:
		std::cout << "멋진 차량이 완성되었습니다.\n";
		std::cout << "어떤 동작을 할까요?\n";
		std::cout << "0. 처음 화면으로 돌아가기\n";
		std::cout << "1. RUN\n";
		std::cout << "2. Test\n";

		break;
	}
	std::cout << "===============================\n";
}

bool checkPart(int step, int answer, PartPubisherList publishers)
{
	std::string failReason = "";

	// 정합성 확인
	if (Condition::isValidCarType(step, answer, publishers))
	{
		failReason = "ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n";
	}
	else if (Condition::isValidEngineType(step, answer, publishers))
	{
		failReason = "ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n";
	}
	else if (Condition::isValidBrakeType(step, answer, publishers))
	{
		failReason = "ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n";
	}
	else if (Condition::isValidSteeringType(step, answer, publishers))
	{
		failReason = "ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n";
	}
	else if (Condition::isValidTestType(step, answer))
	{
		failReason = "ERROR :: Run 또는 Test 중 하나를 선택 필요\n";
	}

	// 정합성에 따라 결과 출력
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