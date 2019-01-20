#include "stdafx.h"
#include "politician.h"


Politician::Politician(std::string firstName, std::string lastName, Characteristics traits) :
	Person(firstName, lastName, ""), characteristics_(traits) { }

Politician::Politician(Person person, Characteristics traits, Listener *parliament) :
	Person(person), characteristics_(traits) {

	listeners_.push_back(parliament);
}

Politician::Politician(const Politician &politician) : 
	Person(politician.getFirstName(), politician.getLastName(), politician.getDescription()), 
	characteristics_(politician.getCharacteristics()) {

	hello_ = politician.hello_;
	goodbye_ = politician.goodbye_;
	ideas_ = politician.ideas_;
	opinionHistory_ = politician.opinionHistory_;
	listeners_ = politician.listeners_;
}

const bool Politician::isAvailable() {
	return available_.try_lock();
}

void Politician::setAvailable() {
	available_.unlock();
}

const Characteristics Politician::getCharacteristics() const {

	return characteristics_;
}

bool Politician::addIdea(const Idea* newIdea) {

	if (newIdea == nullptr || ideas_.size() == MAXIDEAS) {
		return false;
	}

	//Check if politician already has this idea
	for (std::vector<const Idea*>::const_iterator it = ideas_.begin(); it != ideas_.end(); ++it) {
		if (*it == newIdea) {
			return false;
		}
	}
	ideas_.emplace_back(newIdea);

	//History must be cleared as new idea alters MP's characteristic distance from ideas
	opinionHistory_.clear();

	Event update(Event::addedIdea, this, newIdea);
	notifyListeners(update);

	return true;
}

bool Politician::removeIdea(const Idea* oldIdea) {

	if (oldIdea == nullptr) {
		return false;
	}

	for (std::vector<const Idea*>::const_iterator it = ideas_.begin(); it != ideas_.end(); ++it) {

		if (*it == oldIdea) {
			ideas_.erase(it);

			//History must be cleared as new idea alters MP's characteristic distance from ideas
			opinionHistory_.clear();

			Event update(Event::lostIdea, this, oldIdea);
			notifyListeners(update);

			return true;
		}
	}

	return false;
}

const bool Politician::hasIdea(const Idea* idea) const {

	for (std::vector<const Idea*>::const_iterator it = ideas_.begin(); it != ideas_.end(); ++it) {
		if (*it == idea) {
			return true;
		}
	}
	return false;
}


const std::vector<const Idea*>& Politician::getListOfIdeas() const {

	return ideas_;
}

// The sum of the characteristic differences between the idea
// being considered and those held by the politician
double Politician::ideaIdeaDistance(const Idea* theIdea) {

	double ideaIdeaDistance = 0;

	for (std::vector<const Idea*>::const_iterator ideasIter = ideas_.begin();
		ideasIter != ideas_.end();
		++ideasIter) {

		double distance = theIdea->getCharacteristics().characteristicDistance((*ideasIter)->getCharacteristics());
		
		ideaIdeaDistance += distance;
	}

	return ideaIdeaDistance;
}

double Politician::calculateIdeaDistance(const Idea* idea) {
	double relativeImportance = 0.5;

	double MPIdeaDistance = idea->getCharacteristics().characteristicDistance(getCharacteristics());
	double ideasIdeaDistance = ideaIdeaDistance(idea);

	return abs(MPIdeaDistance) + relativeImportance * abs(ideasIdeaDistance);
}

const Idea* Politician::replaceWeakestIdea(const Idea* idea) {
	const Idea * weakestIdea = getWeakestIdea();
	if ((getListOfIdeas().size() == Politician::MAXIDEAS) && (weakestIdea != idea)) {
		removeIdea(weakestIdea);
	}
	addIdea(idea);

	return weakestIdea;
}

const Idea* Politician::getWeakestIdea() const {

	if (ideas_.size() == 0) {
		return nullptr;
	}

	double greatestDistance = 0, distance = 0;
	std::vector<const Idea*>::const_iterator weakestIdea = getListOfIdeas().begin();

	for (std::vector<const Idea*>::const_iterator nodeIdeaIter = getListOfIdeas().begin();
		nodeIdeaIter != getListOfIdeas().end();
		++nodeIdeaIter) {

		if (distance > greatestDistance) {
			weakestIdea = nodeIdeaIter;
		}
	}

	return *weakestIdea;
}

const bool Politician::persuadedByIdea(const Idea* idea) {

	if (idea == nullptr) {
		return false;
	}

	// Check if MP already has this idea
	for (unsigned int i = 0; i < ideas_.size(); ++i) {
		if (ideas_[i] == idea) {
			return true;
		}
	}

	double ideaDist = calculateIdeaDistance(idea);

	// If MP has less than max number of ideas, they may adopt the idea provided
	// it is within the persuasion threshold
	if (ideas_.size() < MAXIDEAS && ideaDist <= PERSUASION_THRESHOLD) {
		return true;
	}


	// If MP has max number of ideas, they will adopt the new idea if it is
	// less distant than the currently held weakest idea. This condition
	// may be less strict than the above as the weakest idea may not have been
	// added adhering to the threshold rule.
	const Idea* weakestIdea = getWeakestIdea();

	if (weakestIdea != nullptr && ideaDist <= calculateIdeaDistance(getWeakestIdea())) {
		return true;
	}

	return false;
}


const std::string Politician::getOpinion(const Idea* theIdea) {

	if (opinionHistory_.exists(theIdea)) {
		return opinionHistory_.find(theIdea)->second;
	}
	return generateOpinion(theIdea);
}

const std::string Politician::generateOpinion(const Idea* idea) {

	//Find appropriate opinion according to characteristic difference. If the politician possesses the idea then they should fully endorse it,
	//and the characteristics used below are the idea's own characteristics to find a fully endorsing opinion. Else the politician's own
	//characteristics are used

	// First check if the politician already has the idea.
	// If it does, use the idea's characteristics. This ensures
	// the opinion fully endorses the idea (else we could have
	// a contradiction).
	Characteristics characs = characteristics_;
	for (std::vector<const Idea*>::iterator it = ideas_.begin(); it != ideas_.end(); ++it) {
		if (idea == *it) {
			characs = idea->getCharacteristics();
		}
	}

	//Get the available options
	std::vector<Opinion> opinions = idea->getOpinions();

	std::vector<Opinion>::iterator newOpinion;
	double opDist = 9999;

	//Choose the opinion whose characteristic difference with the politician is minimal
	for (std::vector<Opinion>::iterator it = opinions.begin(); it != opinions.end(); ++it) {
		double characDist = characs.characteristicDistance(it->getCharacteristics());
		if (characDist < opDist) {
			newOpinion = it;
			opDist = characDist;
		}
	}

	opinionHistory_.add(idea, newOpinion->getOpinion());
	return newOpinion->getOpinion();
}

Politician::~Politician()
{
}
