#include "stdafx.h"
#include "Conversation.h"
#include <sstream>

Conversation::Conversation(Politician *mp, HistoryLogger<std::string, const Idea*> *seenIdeas, const Idea legislation) : 
	            mp_(mp), seenIdeas_(seenIdeas), legislation_(legislation)
{
	Output::general(introduction());

	Output::switchToConversation();
	Output::politician(mp->sayHello(), mp->getName());

	processCommands();
}

const bool Conversation::politicianAvailable(Politician *mp) {

	return mp->isAvailable();
}

std::string Conversation::introduction() {
	std::string intro = "You approach " + mp_->getName() + " -- " + mp_->getDescription();

	return intro;
}


void Conversation::processCommands() {

	while (true) {
		std::string cmd;
		std::getline(std::cin, cmd);

		if (userCommands::getSupport(cmd)) {
			Output::politician(mp_->getOpinion(&legislation_), mp_->getName());
		}
		else if (userCommands::suggestIdea(cmd)) {
			chooseIdeaToSuggest();
		}
		else if (userCommands::getIdeas(cmd)) {
			getCurrentIdeas();
		}
		else if (userCommands::quit(cmd)) {
			endConversation();
			return;
		}
		else if (userCommands::help(cmd)) {
			getHelp();
		}
		else {
			Output::general("Command not recognised.");
		}
	}
}

std::vector<const Idea*> Conversation::createIdeaList() {

	std::vector<const Idea*> ideaList;

	for (HistoryLogger<std::string, const Idea*>::Iterator it = seenIdeas_->begin(); it != seenIdeas_->end(); ++it) {
		ideaList.push_back(it->second);
	}

	return ideaList;
}

std::string Conversation::createIdeaListString() {

	std::string output;
	int i = 0;
	for (HistoryLogger<std::string, const Idea*>::Iterator it = seenIdeas_->begin(); it != seenIdeas_->end(); ++it, ++i) {
		output += "\t" + std::to_string(i) + ") " + (it->second)->getName() + "\n";
	}
	output += '\t' + std::to_string(seenIdeas_->size()) + ") Never mind";

	return output;
}


void Conversation::chooseIdeaToSuggest() {

	//Create output string for reuse in each loop below
	std::string output = "Which idea would you like to bring their attention to?\n";
	std::vector<const Idea*> ideaList = createIdeaList();
	output += createIdeaListString();

	while (true) {
		Output::general(output);
		std::string ans;
		std::getline(std::cin, ans);
		std::stringstream stream(ans);
		int num;
		if (stream >> num) {
			if (num == seenIdeas_->size()) {
				Output::politician("Anything else?", mp_->getName());
				return;
			}
			else if (num >= 0 && num < seenIdeas_->size()) {
				suggestIdea(ideaList[num]);
				return;
			}
		}
		Output::general("Command not recognised.");
	}
}

std::string Conversation::suggestIdea(const Idea *idea) {

	if (mp_->persuadedByIdea(idea)) {
		Output::politician("I can support that!", mp_->getName());
		mp_->replaceWeakestIdea(idea);
	}
	std::string output = mp_->getOpinion(idea);

	Output::politician(output, mp_->getName());

	return output;
}

void Conversation::getCurrentIdeas() {
	const std::vector<const Idea*> ideaList = mp_->getListOfIdeas();
	std::string currIdeasOutput = "The ideas I currently like are:";

	for (std::vector<const Idea*>::const_iterator it = ideaList.begin(); it != ideaList.end(); ++it) {
		currIdeasOutput += "\n\t" + (*it)->getName();
		seenIdeas_->add((*it)->getName(),*it);
	}

	Output::general(currIdeasOutput);
}

void Conversation::endConversation() {
	std::string output = mp_->getFirstName() + " " + mp_->getLastName() + ": " + mp_->sayGoodbye();
	Output::general(output);
	Output::switchToMainInterface();
}

void Conversation::getHelp() {
	std::string help = "Command options are:\n\tAsk for support\n\tSuggest idea\n\tCurrent ideas\n\tLeave";
	Output::general(help);
}

Conversation::~Conversation()
{
	mp_->setAvailable();
}
