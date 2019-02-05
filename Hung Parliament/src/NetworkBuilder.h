#pragma once
#include "stdafx.h"
#include "politicians.h"
#include "Network.h"
#include "RandomGenerator.h"

class NetworkBuilder
{
	Network<Politician*, double> *network_;

	Network<Politician*, double>* buildLinks(Politician *mp, Politicians &MPs);
	const bool linkExists(Politician *mp1, Politician *mp2);
	const double addProbability(Politician *mp1, Politician *mp2);

public:
	NetworkBuilder();
	Network<Politician*, double>* build(Politicians &MPs, Network<Politician*, double> *network);
	~NetworkBuilder();
};

