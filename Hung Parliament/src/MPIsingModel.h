#pragma once

#include "politician.h"
#include "HistoryLogger.h"

class MPIsingModel
{
	double alpha_ = 4, beta_ = 0.1;
	HistoryLogger<Idea, double> exploredIdeas_;
	Politician* lastMPObserved;

	double ideaIdeaDistance(Politician* mp, const Idea &theIdea);

public:
	const double IDEA_INFLUENCE = 0.5;

	MPIsingModel();
	MPIsingModel(double alpha, double beta, double ideaInfluence);
	double ideaDiffusionProbability(Politician* mp, const Idea &theIdea, double externalInfluence);
	double getTotalExternalInfluence(Politician* mp, const Idea &idea);
	double updateTotalExternalInfluence(const Idea &idea, double externalInfluence);
	double calculateMPIdeaDistance(Politician* mp, const Idea &idea);

	~MPIsingModel();
};

