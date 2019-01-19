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
			suggestIdea();
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

void Conversation::suggestIdea() {

	std::vector<const Idea*> ideaList;

	//Create output string for reuse in each loop below
	std::string output = "Which idea would you like to bring their attention to?\n";
	int i = 0;
	for (HistoryLogger<std::string, const Idea*>::Iterator it = seenIdeas_->begin(); it != seenIdeas_->end(); ++it, ++i) {
		output += "\t" + std::to_string(i) + ") " + (it->second)->getName() + "\n";
		ideaList.push_back(it->second);
	}
	output += '\t' + std::to_string(seenIdeas_->size()) + ") Never mind";

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
				const Idea* suggIdea = ideaList[num];
				Output::politician(mp_->getOpinion(suggIdea), mp_->getName());
				return;
			}
		}
		Output::general("Command not recognised.");
	}
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
