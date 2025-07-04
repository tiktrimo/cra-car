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

#define CLEAR_SCREEN "\033[H\033[2J"

int stack[10];

void selectCarType(int answer);
void selectEngine(int answer);
void selectbrakeSystem(int answer);
void selectSteeringSystem(int answer);
void runProducedCar();
void testProducedCar();
void delay(int ms);

void displayMenu(int step);
bool checkPart(int step, int answer);
bool checkStep(int& step, int answer);
void processPartsSelctionStep(int step, int answer);
void processRunStep(int answer);
void nextStep(int& step, int answer);

enum QuestionType
{
	CarType_Q,
	Engine_Q,
	brakeSystem_Q,
	SteeringSystem_Q,
	Run_Test,
};

enum CarType
{
	SEDAN = 1,
	SUV,
	TRUCK
};
std::string carTypeNamesRaw[4] = { "",  "SEDAN", "SUV", "TRUCK" };
std::string carTypeNames[4] = { "",  "Sedan", "SUV", "Truck" };

enum Engine
{
	GM = 1,
	TOYOTA,
	WIA
};
std::string engineNamesRaw[4] = { "",  "GM", "TOYOTA", "WIA" };
std::string engineNames[4] = { "",  "GM", "TOYOTA", "WIA" };

enum brakeSystem
{
	MANDO = 1,
	CONTINENTAL,
	BOSCH_B
};
std::string brakeSystemNamesRaw[4] = { "", "MANDO", "CONTINENTAL", "BOSCH" };
std::string brakeSystemNames[4] = { "", "Mando", "Cnotinental", "Bosch" };

enum SteeringSystem
{
	BOSCH_S = 1,
	MOBIS
};
std::string steeringSystemNamesRaw[3] = { "", "BOSCH", "MOBIS" };
std::string steeringSystemNames[3] = { "", "Bosch", "Mobis" };

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

	static void trimInput(std::string& input)
	{
		input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());
		input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
	}
};

class Condition
{
public:
	static bool isExit(std::string input)
	{
		return input == "exit";
	}

	static bool isNumber(std::string input)
	{
		std::string::const_iterator it = input.begin();
		while (it != input.end() && std::isdigit(*it)) ++it;
		return !input.empty() && it == input.end();
	}

	static bool isValidCarType(int step, int answer)
	{
		return step == CarType_Q && !(answer >= 1 && answer <= 3);
	}

	static bool isValidEngineType(int step, int answer)
	{
		return step == Engine_Q && !(answer >= 0 && answer <= 4);
	}

	static bool isValidBrakeType(int step, int answer)
	{
		return step == brakeSystem_Q && !(answer >= 0 && answer <= 3);
	}

	static bool isValidSteeringType(int step, int answer)
	{
		return step == SteeringSystem_Q && !(answer >= 0 && answer <= 2);
	}

	static bool isValidTestType(int step, int answer)
	{
		return step == Run_Test && !(answer >= 0 && answer <= 2);
	}
};

class Util
{
public:
	static int getNumebr(std::string input)
	{
		return std::stoi(input);
	}
};


int main()
{
	int step = CarType_Q;
	while (true)
	{
		displayMenu(step);

		std::string input = Screen::getInput();
		Screen::trimInput(input);

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

		if (checkPart(step, answer))
		{
			continue;
		}
		else if (checkStep(step, answer))
		{
			continue;
		}

		nextStep(step, answer);
	}
}

void selectCarType(int answer)
{
	stack[CarType_Q] = answer;
	std::cout << "차량 타입으로 " + carTypeNamesRaw[answer] + "을 선택하셨습니다.\n";
}

void selectEngine(int answer)
{
	stack[Engine_Q] = answer;
	std::cout << engineNamesRaw[answer] + " 엔진을 선택하셨습니다.\n";
}

void selectbrakeSystem(int answer)
{
	stack[brakeSystem_Q] = answer;
	std::cout << brakeSystemNamesRaw[answer] + " 제동장치를 선택하셨습니다.\n";
}

void selectSteeringSystem(int answer)
{
	stack[SteeringSystem_Q] = answer;
	std::cout << steeringSystemNamesRaw[answer] + " 조향장치를 선택하셨습니다.\n";
}

int isValidCheck()
{
	if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
	{
		return false;
	}
	else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
	{
		return false;
	}
	else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
	{
		return false;
	}
	else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
	{
		return false;
	}
	else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
	{
		return false;
	}

	return true;
}

void runProducedCar()
{
	if (isValidCheck() == false)
	{
		std::cout << "자동차가 동작되지 않습니다\n";
		return;
	}
	if (stack[Engine_Q] == 4)
	{
		std::cout << "엔진이 고장나있습니다.\n";
		std::cout << "자동차가 움직이지 않습니다.\n";
		return;
	}

	std::cout << "Car Type : " + carTypeNames[stack[CarType_Q]] + "\n";
	std::cout << "Engine : " + engineNames[stack[Engine_Q]] + "\n";
	std::cout << "Brake System : " + brakeSystemNames[stack[brakeSystem_Q]] + "\n";
	std::cout << "Steering System : " + steeringSystemNames[stack[SteeringSystem_Q]] + "\n";

	std::cout << "자동차가 동작됩니다.\n";
}

void testProducedCar()
{
	std::string failReason = "";
	std::string failMessage = "자동차 부품 조합 테스트 결과 : FAIL\n";
	std::string successMessage = "자동차 부품 조합 테스트 결과 : PASS\n";

	// 정합성이 맞는지 확인
	if (stack[CarType_Q] == SEDAN && stack[brakeSystem_Q] == CONTINENTAL)
	{
		failReason = "Sedan에는 Continental제동장치 사용 불가\n";
	}
	else if (stack[CarType_Q] == SUV && stack[Engine_Q] == TOYOTA)
	{
		failReason = "SUV에는 TOYOTA엔진 사용 불가\n";
	}
	else if (stack[CarType_Q] == TRUCK && stack[Engine_Q] == WIA)
	{
		failReason = "Truck에는 WIA엔진 사용 불가\n";
	}
	else if (stack[CarType_Q] == TRUCK && stack[brakeSystem_Q] == MANDO)
	{
		failReason = "Truck에는 Mando제동장치 사용 불가\n";
	}
	else if (stack[brakeSystem_Q] == BOSCH_B && stack[SteeringSystem_Q] != BOSCH_S)
	{
		failReason = "Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n";
	}

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

void displayMenu(int step)
{
	std::cout << CLEAR_SCREEN;

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
		std::cout << "1. Sedan\n";
		std::cout << "2. SUV\n";
		std::cout << "3. Truck\n";

		break;

	case Engine_Q:
		std::cout << "어떤 엔진을 탑재할까요?\n";
		std::cout << "0. 뒤로가기\n";
		std::cout << "1. GM\n";
		std::cout << "2. TOYOTA\n";
		std::cout << "3. WIA\n";
		std::cout << "4. 고장난 엔진\n";

		break;

	case brakeSystem_Q:
		std::cout << "어떤 제동장치를 선택할까요?\n";
		std::cout << "0. 뒤로가기\n";
		std::cout << "1. MANDO\n";
		std::cout << "2. CONTINENTAL\n";
		std::cout << "3. BOSCH\n";

		break;

	case SteeringSystem_Q:
		std::cout << "어떤 조향장치를 선택할까요?\n";
		std::cout << "0. 뒤로가기\n";
		std::cout << "1. BOSCH\n";
		std::cout << "2. MOBIS\n";

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

bool checkPart(int step, int answer)
{
	std::string failReason = "";

	// 정합성 확인
	if (Condition::isValidCarType(step, answer))
	{
		failReason = "ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n";
	}
	else if (Condition::isValidEngineType(step, answer))
	{
		failReason = "ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n";
	}
	else if (Condition::isValidBrakeType(step, answer))
	{
		failReason = "ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n";
	}
	else if (Condition::isValidSteeringType(step, answer))
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

void processPartsSelctionStep(int step, int answer)
{
	switch (step)
	{
	case CarType_Q:
		selectCarType(answer);
		break;
	case Engine_Q:
		selectEngine(answer);
		break;
	case brakeSystem_Q:
		selectbrakeSystem(answer);
		break;
	case SteeringSystem_Q:
		selectSteeringSystem(answer);
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

void nextStep(int& step, int answer)
{
	if (step <= SteeringSystem_Q)
	{
		processPartsSelctionStep(step, answer);
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