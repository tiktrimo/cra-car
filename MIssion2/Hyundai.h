#pragma once
#include "PartPublisher.h"
#include "string"

class Hyundai : public PartPublisher
{
public:
	Hyundai()
	{
		name = "WIA";
		isEngineFab = true;
	}
};