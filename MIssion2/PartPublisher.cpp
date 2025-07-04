#include "PartPublisher.h"

std::string PartPublisher::getName()
{
	return name;
}

std::string PartPublisher::getNameUppercase()
{
	std::string nameUpper = name;
	for (auto& c : nameUpper) c = toupper(c);

	return nameUpper;
}

std::string PartPublisher::getCar()
{
	return "차량 타입으로 " + getNameUppercase() + "을 선택하셨습니다.\n";
}

std::string PartPublisher::getEngine()
{
	return getNameUppercase() + " 엔진을 선택하셨습니다.\n";
}

std::string PartPublisher::getBrake()
{
	return getNameUppercase() + " 제동장치를 선택하셨습니다.\n";
}

std::string PartPublisher::getSteering()
{
	return  getNameUppercase() + " 조향장치를 선택하셨습니다.\n";
}