#pragma once
#include "PartPublisher.h"
#include "string"

class Bosch : public PartPublisher
{
public:
	Bosch()
	{
		name = "Bosch";
		isBrakeFab = true;
		isSteeringFab = true;
	}
};