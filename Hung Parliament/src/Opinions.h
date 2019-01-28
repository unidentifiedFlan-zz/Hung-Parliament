#pragma once
#include "stdafx.h"
#include "Opinion.h"

class Opinions
{
	std::set<Opinion> opinions_;
	std::set<Opinion>::iterator next_;
public:
	typedef std::set<Opinion>::iterator Iterator;
	Opinions();
	void add(const Opinion &opinion);
	void remove(const Opinion &opinion);
	void clear();
	bool include(const Opinion &opinion) const;

	unsigned int numberOf() const;
	Iterator getFirst();
	Iterator getLast();

	

	virtual ~Opinions();
};

