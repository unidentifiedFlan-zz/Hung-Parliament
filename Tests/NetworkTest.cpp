#include "pch.h"
#include "../Hung Parliament/src/Network.h"
#include <stdlib.h>

class networkTest : public ::testing::Test {

public:

	class object {
		int _ref;
	public:
		object(int newRef) : _ref(newRef) {}
		int getRef() { return _ref; }
		void setRef(int val) { _ref = val; }
	};

	virtual void SetUp() {

		o = new object(41167);
		p = new object(10765);
		q = new object(28193);

		_network.addNode(o);
		_network.addNode(p);
		_network.addNode(q);


	}

	virtual void TearDown() {
		delete o;
		delete p;
		delete q;
	}

	Network<object*, int> _network;
	object *o, *p, *q;
};

TEST_F(networkTest, addNodeTest) {

	int sum(0);

	for (Network<object*, int>::iterator it = _network.begin(); it != _network.end(); ++it) {

		sum += it->first->getRef();
	}

	ASSERT_EQ(41167 + 10765 + 28193, sum);

	o->setRef(111);

	sum= 0;

	for (Network<object*, int>::iterator it = _network.begin(); it != _network.end(); ++it) {

		sum += it->first->getRef();
	}

	ASSERT_EQ(111 + 10765 + 28193, sum);

}

TEST_F(networkTest, deleteNodeTest) {

	int sum(0);

	for (Network<object*, int>::iterator it = _network.begin(); it != _network.end(); ++it) {

		sum += it->first->getRef();
	}

	ASSERT_EQ(41167 + 10765 + 28193, sum);

	_network.deleteNode(q);
	sum = 0;

	for (Network<object*, int>::iterator it = _network.begin(); it != _network.end(); ++it) {

		sum += it->first->getRef();
	}

	ASSERT_EQ(41167 + 10765, sum);
}

TEST_F(networkTest, adjacentNodeTest) {

	_network.addLink(o, p, 1);
	_network.addLink(o, q, 2);
	_network.addLink(p, q, 3);

	std::vector<Network<object*, int>::Edge> adjNodes(_network.getAdjacentNodes(o));
	int sum(0);

	for(std::vector<Network<object*, int>::Edge>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it) {
		sum += it->adjacentNode->get->getRef();
	}
	ASSERT_EQ(10765 + 28193, sum);

	sum = 0;
	adjNodes = _network.getAdjacentNodes(p);

	for (std::vector<Network<object*, int>::Edge>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it) {
		sum += it->adjacentNode->get->getRef();
	}
	ASSERT_EQ(28193, sum);

	sum = 0;
	adjNodes = _network.getAdjacentNodes(q);

	for (std::vector<Network<object*, int>::Edge>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it) {
		sum += it->adjacentNode->get->getRef();
	}
	ASSERT_EQ(0, sum);

	_network.deleteLink(o, p);
	sum = 0;
	adjNodes = _network.getAdjacentNodes(o);

	for (std::vector<Network<object*, int>::Edge>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it) {
		sum += it->adjacentNode->get->getRef();
	}
	ASSERT_EQ(28193, sum);
}