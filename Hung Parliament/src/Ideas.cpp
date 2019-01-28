#include "Ideas.h"

Ideas::Ideas()
{}

void Ideas::add(const Idea &idea) {

	ideas_.insert(idea);
}

void Ideas::remove(const Idea &idea) {

	ideas_.erase(idea);
}

void Ideas::clear() {
	ideas_.clear();
}

bool Ideas::includes(const Idea &idea) const {

	Iterator it = ideas_.find(idea);

	if (it != ideas_.end()) {
		return true;
	}
	
	return false;
}

unsigned int Ideas::numberOf() const {
	return ideas_.size();
}

Ideas::Iterator Ideas::getFirst() const {

	return ideas_.begin();
}

Ideas::Iterator Ideas::getLast() const {

	return ideas_.end();
}

Ideas::~Ideas()
{
}
