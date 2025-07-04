#pragma once
#include <string>


#include "Sedan.h"
#include "Suv.h"
#include "Truck.h"

#include "GeneralMotors.h"
#include "Toyota.h"
#include "Hyundai.h"

#include "Mando.h"
#include "Continental.h"
#include "Bosch.h"

#include "Mobis.h"
#include "Broken.h"

class PartPubisherList
{
public:
	PartPubisherList()
	{
		publishers = {
			new Sedan(),
			new Suv(),
			new Truck(),
			new GeneralMotors(),
			new Toyota(),
			new Hyundai(),
			new Mando(),
			new Continental(),
			new Bosch(),
			new Mobis(),
			new Broken()
		};
	}

	std::string getCarFabs();
	std::string getEngineFabs();
	std::string getBrakeFabs();
	std::string getSteeringFabs();

	PartPublisher* findCarFabs(int target);
	PartPublisher* findEngineFabs(int target);
	PartPublisher* findBrakFabs(int target);
	PartPublisher* findSteeringFabs(int target);


	int getCarFabsCnt();
	int getEngineFabsCnt();
	int getBrakeFabsCnt();
	int getSteeringFabsCnt();

private:
	std::vector<PartPublisher*> publishers;
};