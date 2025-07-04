#pragma once
#include "PartPublisher.h"
#include "string"

class Broken : public PartPublisher
{
public:
	Broken()
	{
		name = "Broken";
		isEngineFab = true;
	}
};