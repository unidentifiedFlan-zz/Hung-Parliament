#include "Opinions.h"


Opinions::Opinions() {}

void Opinions::add(const Opinion &opinion) {
	opinions_.insert(opinion);
}

void Opinions::remove(const Opinion &opinion) {
	opinions_.erase(opinion);
}

void Opinions::clear() {
	opinions_.clear();
}

bool Opinions::include(const Opinion &opinion) const {

	std::set<Opinion>::const_iterator it = opinions_.find(opinion);

	if (it != opinions_.end()) {
		return true;
	}

	return false;
}

unsigned int Opinions::numberOf() const {
	return opinions_.size();
}

Opinions::Iterator Opinions::getFirst() {
	return opinions_.begin();
}

Opinions::Iterator Opinions::getLast() {
	return opinions_.end();
}

Opinions::~Opinions()
{
}
