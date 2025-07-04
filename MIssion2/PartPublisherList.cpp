#include "PartPublisherList.h"

std::string PartPubisherList::getCarFabs()
{
	int number = 1;
	std::string result = "";
	for (auto publisher : publishers) {
		if (publisher->isCarFab == false) continue;
		result += std::to_string(number++) + ". " + publisher->getNameUppercase() + "\n";
	}

	return result;
}

std::string PartPubisherList::getEngineFabs()
{
	int number = 1;
	std::string result = "";
	for (auto publisher : publishers) {
		if (publisher->isEngineFab == false) continue;
		result += std::to_string(number++) + ". " + publisher->getNameUppercase() + "\n";
	}

	return result;
}

std::string PartPubisherList::getBrakeFabs()
{
	int number = 1;
	std::string result = "";
	for (auto publisher : publishers) {
		if (publisher->isBrakeFab == false) continue;
		result += std::to_string(number++) + ". " + publisher->getNameUppercase() + "\n";
	}

	return result;
}

std::string PartPubisherList::getSteeringFabs()
{
	int number = 1;
	std::string result = "";
	for (auto publisher : publishers) {
		if (publisher->isSteeringFab == false) continue;
		result += std::to_string(number++) + ". " + publisher->getNameUppercase() + "\n";
	}

	return result;
}

PartPublisher* PartPubisherList::findCarFabs(int target)
{
	int number = 1;
	for (auto publisher : publishers) {
		if (publisher->isCarFab == false) continue;
		if (number++ == target) return publisher;
	}
}

PartPublisher* PartPubisherList::findEngineFabs(int target)
{
	int number = 1;
	for (auto publisher : publishers) {
		if (publisher->isEngineFab == false) continue;
		if (number++ == target) return publisher;
	}
}

PartPublisher* PartPubisherList::findBrakFabs(int target)
{
	int number = 1;
	for (auto publisher : publishers) {
		if (publisher->isBrakeFab == false) continue;
		if (number++ == target) return publisher;
	}
}

PartPublisher* PartPubisherList::findSteeringFabs(int target)
{
	int number = 1;
	for (auto publisher : publishers) {
		if (publisher->isSteeringFab == false) continue;
		if (number++ == target) return publisher;
	}
}

int PartPubisherList::getCarFabsCnt() 
{
	int number = 1;
	for (auto publisher : publishers) {
		if (publisher->isCarFab == false) continue;
		number++;
	}
	return number;
}

int PartPubisherList::getEngineFabsCnt() 
{
	int number = 1;
	for (auto publisher : publishers) {
		if (publisher->isEngineFab == false) continue;
		number++;
	}
	return number;
}

int PartPubisherList::getBrakeFabsCnt() 
{
	int number = 1;
	for (auto publisher : publishers) {
		if (publisher->isBrakeFab == false) continue;
		number++;
	}
	return number;
}

int PartPubisherList::getSteeringFabsCnt() 
{
	int number = 1;
	for (auto publisher : publishers) {
		if (publisher->isSteeringFab == false) continue;
		number++;
	}
	return number;
}