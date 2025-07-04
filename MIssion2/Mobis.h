#pragma once
#include "PartPublisher.h"
#include "string"

class Mobis : public PartPublisher
{
public:
	Mobis()
	{
		name = "Mobis";
		isSteeringFab = true;
	}
};