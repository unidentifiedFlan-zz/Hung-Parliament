#pragma once
#include "stdafx.h"
#include "Network.h"

template <class T, class U>
class AbstractNetworkDynamics : public Network<T, U>
{
protected:

	double getRandomDouble() {

		return (double)rand() / RAND_MAX;
	}

public:
	AbstractNetworkDynamics() {}
	virtual void runDynamics(bool *quit) {};

	const T getRandomNode() {
		// Probabilities proportional to number of links.
		// Store total number of links. Prob. per link = 1.0/totalNumLinks.
		// Prob. of gettingNode = numNodeLinks*Prob per link. 

		double randDouble = getRandomDouble();
		double sum = 0;
		double step = 1 / Network<T, U>::NUM_LINKS;
		for (typename Network<T,U>::iterator it = Network<T,U>::network_.begin(); it != Network<T, U>::network_.end(); ++it) {

			sum += ((double)it->second.edges.size())*step;
			if (randDouble < sum) {
				return it->first;
			}
		}

		return Network<T, U>::network_.begin()->first;
	}

	virtual ~AbstractNetworkDynamics() {}
};