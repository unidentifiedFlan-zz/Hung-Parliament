#pragma once

#include "AbstractNetworkDynamics.h"
#include "politician.h"
#include "HistoryLogger.h"

class MPIsingModel : public AbstractNetworkDynamics<Politician*, double>
{

	time_t _runInterval;
	time_t _lastRunTime;

	HistoryLogger<const Idea*, double> _exploredIdeas;

	void getIdeasFromAdjacentMPs(Politician* randMP, const std::vector<Network<Politician*, double>::Edge> adjNodes);
	void compareAdjacentIdeas(Politician* currentMP, Network<Politician*, double>::Edge linkedMP);

public:
	MPIsingModel(int interval);
	void runDynamics(bool *quit);
	double ideaDiffusionProbability(Politician* currentMP, const Idea* theIdea);

	~MPIsingModel();
};

