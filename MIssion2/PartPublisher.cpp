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
	return "���� Ÿ������ " + getNameUppercase() + "�� �����ϼ̽��ϴ�.\n";
}

std::string PartPublisher::getEngine()
{
	return getNameUppercase() + " ������ �����ϼ̽��ϴ�.\n";
}

std::string PartPublisher::getBrake()
{
	return getNameUppercase() + " ������ġ�� �����ϼ̽��ϴ�.\n";
}

std::string PartPublisher::getSteering()
{
	return  getNameUppercase() + " ������ġ�� �����ϼ̽��ϴ�.\n";
}