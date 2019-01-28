#include "stdafx.h"
#include "politician.h"
#include "MPIsingModel.h"


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

bool Politician::addIdea(const Idea &newIdea) {

	//Check if politician already has this idea
	if (ideas_.includes(newIdea)) {

		return false;
	}

	ideas_.add(newIdea);

	//History must be cleared as new idea alters MP's characteristic distance from ideas
	opinionHistory_.clear();

	Event update(Event::addedIdea, this, newIdea);
	notifyListeners(update);

	return true;
}

bool Politician::removeIdea(const Idea &oldIdea) {

	for (Ideas::Iterator it = ideas_.getFirst(); it != ideas_.getLast(); ++it) {

		if (*it == oldIdea) {
			ideas_.remove(*it);

			//History must be cleared as new idea alters MP's characteristic distance from ideas
			opinionHistory_.clear();

			Event update(Event::lostIdea, this, oldIdea);
			notifyListeners(update);

			return true;
		}
	}

	return false;
}

const bool Politician::hasIdea(const Idea &idea) const {

	return ideas_.includes(idea);
}

const Ideas& Politician::getIdeas() const {

	return ideas_;
}

const Idea& Politician::getWeakestIdea() {

	double greatestDistance = 0, distance = 0;
	Ideas::Iterator weakestIdea = ideas_.getFirst();

	for (Ideas::Iterator nodeIdeaIter = ideas_.getFirst();
		nodeIdeaIter != ideas_.getLast();
		++nodeIdeaIter) {

		distance = characteristics_.characteristicDistance(nodeIdeaIter->getCharacteristics());

		if (distance > greatestDistance) {
			weakestIdea = nodeIdeaIter;
			greatestDistance = distance;
		}
	}

	return *weakestIdea;
}

const bool Politician::replaceWeakestIdea(const Idea &idea) {

	if (ideas_.numberOf() > 0) {
		const Idea weakestIdea = getWeakestIdea();

		if (weakestIdea == idea) {
			return false;
		}

		if (ideas_.numberOf() == Politician::MAXIDEAS) {
			removeIdea(weakestIdea);
		}
	}

	addIdea(idea);

	return true;
}

const bool Politician::persuadedByIdea(const Idea &idea) {

	MPIsingModel model;
	// Check if MP already has this idea
	if (ideas_.includes(idea)) {
		return true;
	}

	double ideaDist = model.calculateMPIdeaDistance(this, idea);

	// If MP has less than max number of ideas, they may adopt the idea provided
	// it is within the persuasion threshold
	if (ideas_.numberOf() < Politician::MAXIDEAS && ideaDist <= PERSUASION_THRESHOLD) {
		return true;
	}


	// If MP has max number of ideas, they will adopt the new idea if it is
	// less distant than the currently held weakest idea. This condition
	// may be less strict than the above as the weakest idea may not have been
	// added adhering to the threshold rule.
	if (ideas_.numberOf() > 0) {

		const Idea weakestIdea = getWeakestIdea();

		if (ideaDist <= model.calculateMPIdeaDistance(this, weakestIdea)) {

			return true;
		}

	}

	return false;
}

const Opinion Politician::getOpinion(const Idea &idea) {

	if (opinionHistory_.exists(idea)) {
		return opinionHistory_.find(idea)->second;
	}
	return generateOpinion(idea);
}

const Opinion Politician::generateOpinion(const Idea &idea) {

	//Find appropriate opinion according to characteristic difference. If the politician possesses the idea then they should fully endorse it,
	//and the characteristics used below are the idea's own characteristics to find a fully endorsing opinion. Else the politician's own
	//characteristics are used

	// First check if the politician already has the idea.
	// If it does, use the idea's characteristics. This ensures
	// the opinion fully endorses the idea (else we could have
	// a contradiction).
	Characteristics characs = characteristics_;
	for (Ideas::Iterator it = ideas_.getLast(); it != ideas_.getLast(); ++it) {
		if (idea == *it) {
			characs = idea.getCharacteristics();
		}
	}

	//Get the available options
	Opinions opinions = idea.getOpinions();

	Opinions::Iterator newOpinion;
	double opDist = 9999;

	//Choose the opinion whose characteristic difference with the politician is minimal
	for (Opinions::Iterator it = opinions.getFirst(); it != opinions.getLast(); ++it) {
		double characDist = characs.characteristicDistance(it->getCharacteristics());
		if (characDist < opDist) {
			newOpinion = it;
			opDist = characDist;
		}
	}

	opinionHistory_.add(idea, *newOpinion);
	return *newOpinion;
}

Politician::~Politician()
{
}
