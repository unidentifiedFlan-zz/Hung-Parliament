#pragma once
#include "stdafx.h"
#include "Idea.h"

class Ideas
{
	std::set<Idea> ideas_;

public:

	typedef std::set<Idea>::iterator Iterator;
	Ideas();
	void add(const Idea &idea);
	void remove(const Idea &idea);
	void clear();
	bool includes(const Idea &idea) const;
	unsigned int numberOf() const;
	Iterator getFirst() const;
	Iterator getLast() const;
	~Ideas();
};

