#pragma once

#include <time.h>
#include "stdafx.h"
#include <iterator>

template <class T, class U>
class Network {

public:

	struct Node;

	struct Edge {
		U weight;
		Node* adjacentNode;
		Edge(Node* node, U wgt) : adjacentNode(node), weight(wgt) {}
	};

	struct Node {
		T get;
		std::vector<Edge> edges;
		Node(T& object) : get(object) {}
	};

	typedef typename std::unordered_map<T, Node>::iterator iterator;

	Network() {
		srand(static_cast<unsigned int>(time(0)));
	}

	bool addNode(T& node) {
		if (network_.find(node) == network_.end()) {
			Node newNode(node);
			network_.emplace(node, newNode);
			return true;
		}
		return false;
	}

	bool deleteNode(T& node) {

		iterator it = network_.find(node);

		if (it != network_.end()) {
			network_.erase(it);
			return true;
		}
		return false;
	}

	//Add a unidirectional weighted link from node1 to node2
	bool addLink(T& node1, T& node2, U linkValue) {
		
		iterator it1 = network_.find(node1);
		if (it1 != network_.end()) {
			iterator it2 = network_.find(node2);
			if (it2 != network_.end()) {
				Edge newEdge(&it2->second, linkValue);
				it1->second.edges.push_back(newEdge);
				NUM_LINKS++;
				return true;
			}
		}
		
		return false;
	}


	bool deleteLink(T& node1, T& node2) {

		iterator it1 = network_.find(node1);
		if (it1 != network_.end()) {
			for (typename std::vector<Edge>::iterator itAdj = it1->second.edges.begin(); itAdj != it1->second.edges.end(); ++itAdj) {

				if (itAdj->adjacentNode->get == node2) {
					it1->second.edges.erase(itAdj);
					NUM_LINKS--;
					return true;
				}
			}
		}
		return false;
	}

	unsigned int size() {
		return network_.size();
	}

	iterator begin() {
		return network_.begin();
	}

	iterator end() {
		return network_.end();
	}

	const std::vector<Edge> getAdjacentNodes(T& node) {

		iterator it = network_.find(node);
		if (it != network_.end()) {
			return it->second.edges;
		}
		
		std::vector<Edge> emptyVec;
		return emptyVec;
	}

	const bool nodeValid(T& node) {

		iterator it = network_.find(node);
		if (it != network_.end()) {
			return true;
		}
		
		return false;
	}
	virtual ~Network() {}

	protected:
		std::unordered_map<T, Node> network_;
		double NUM_LINKS = 0;
};