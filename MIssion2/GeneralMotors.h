#pragma once
#include "PartPublisher.h"
#include "string"

class GeneralMotors : public PartPublisher
{
public:
	GeneralMotors()
	{
		name = "GM";
		isEngineFab = true;
	}
};