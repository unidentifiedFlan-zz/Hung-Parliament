#pragma once
class Politician;
class Idea;

struct Event
{
	enum Type {addedIdea, lostIdea};

	Type type;
	Politician *politician;
	const Idea &idea;
	const int value = -1;
	Event(Type t, Politician *p, const Idea &i) : type(t), politician(p), idea(i) {}
	~Event(){}
};

