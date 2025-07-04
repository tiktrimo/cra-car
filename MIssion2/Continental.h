#pragma once
#include "PartPublisher.h"
#include "string"

class Continental : public PartPublisher
{
public:
	Continental() 
	{
		name = "Continental";
		isBrakeFab = true;
	}
};