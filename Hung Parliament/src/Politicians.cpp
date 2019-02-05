#include "Politicians.h"


Politicians::Politicians()
{
}

void Politicians::add(Politician &politician) {

	politicians_.emplace(politician.getName(), politician);
}

void Politicians::remove(Politician &politician) {

	politicians_.erase(politician.getName());
}

void Politicians::clear() {
	politicians_.clear();
}

bool Politicians::includes(std::string name) {

	Iterator it = find(name);

	if (it != getLast()) {
		return true;
	}

	return false;
}

Politicians::Iterator Politicians::find(std::string name) {

	std::unordered_map<std::string, Politician>::iterator politicianIter = politicians_.find(name);

	Iterator iter(politicianIter);
	return iter;
}

unsigned int Politicians::numberOf() const {
	return politicians_.size();
}

Politicians::Iterator Politicians::getFirst() {

	std::unordered_map<std::string, Politician>::iterator iter = politicians_.begin();
	Iterator first(iter);
	return first;
}

Politicians::Iterator Politicians::getLast() {

	std::unordered_map<std::string, Politician>::iterator iter = politicians_.end();
	Iterator last(iter);
	return last;
}

Politicians::~Politicians()
{
}
