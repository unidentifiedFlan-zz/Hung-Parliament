#pragma once
#include "stdafx.h"
#include "Politician.h"
#include "Network.h"

class PoliticianLists
{
public:

	struct Connections {
		const Politician *politician;
		int value;
		Connections(const Politician *pol, int num) : politician(pol), value(num) {}
	};

	struct Influence {
		const Politician* politician;
		double value;
		Influence(const Politician *pol, double inf) : politician(pol), value(inf) {}
	};

	PoliticianLists(Network<Politician*, double> *nodes);
	std::vector<Connections> getMostConnectedList();
	std::vector<Influence> getMostInfluentialList();
	std::string printMostInfluential(int num);
	std::string printMostConnected(int num);
	~PoliticianLists();

private:
	template <class T>
	class LargestFirst {
	public:
		bool operator () (const T &v1, T &v2) {
			return v1.value > v2.value;
		}
	};

	std::vector<Connections> mostConnected_;
	std::vector<Influence> mostInfluential_;

	std::vector<Connections> initialiseMostConnectedList(Network<Politician*, double> *network);
	std::vector<Influence> initialiseMostInfluentialList(Network<Politician*, double> *network);
	double calculateInfluence(double influence, int numConnections);
};

