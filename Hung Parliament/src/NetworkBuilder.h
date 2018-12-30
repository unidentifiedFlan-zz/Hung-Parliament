#pragma once
#include "stdafx.h"
#include "politician.h"
#include "Network.h"

class NetworkBuilder
{
	Network<Politician*, double> *network_;

	Network<Politician*, double>* buildLinks(Politician *mp, std::unordered_map<std::string, Politician> &MPs);
	const bool linkExists(Politician *mp1, Politician *mp2);
	const double addProbability(Politician *mp1, Politician *mp2);
	const double randNum();

public:
	NetworkBuilder();
	Network<Politician*, double>* build(std::unordered_map<std::string, Politician> &MPs, Network<Politician*, double> *network);
	~NetworkBuilder();
};

