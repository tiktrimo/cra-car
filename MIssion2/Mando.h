#pragma once
#include "PartPublisher.h"
#include "string"

class Mando : public PartPublisher
{
public:
	Mando()
	{
		name = "Mando";
		isBrakeFab = true;
	}
};