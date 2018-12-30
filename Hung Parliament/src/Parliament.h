#pragma once
#include "stdafx.h"
#include <stack>
#include "Listener.h"
#include "Politician.h"
#include "AbstractNetworkDynamics.h"
#include "PoliticianLists.h"

class Parliament : public Listener, public Publisher
{
	std::vector<std::string> characteristicNames_ = { "egalitarian", "econLib", "authoritarian" };
	
	int numMPs_ = 0;
	std::unordered_map<std::string, Politician> MPs_;

	std::stack<Idea> legislation_;
	std::vector<Idea> ideas_;

	AbstractNetworkDynamics<Politician*, double> *network_;
	std::unordered_map<std::string, Politician>::iterator MPIter = MPs_.begin();
	
public:
	Parliament(int numMPs, AbstractNetworkDynamics<Politician*, double> *network);

	void handleEvent(Event &e);

	Politician* findMP(std::string mp);
	std::vector<Network<Politician*, double>::Edge> getMPConnections(Politician* mp) const;
    Politician* getNextMP();
	int getNumberOfMPs();
	PoliticianLists createPoliticianLists();

	Idea getLegislation();
	bool calculateMPSupport(Politician *mp) const;

	~Parliament();
};

