#include "stdafx.h"
#include "Conversation.h"
#include <sstream>

Conversation::Conversation(Politician *mp, HistoryLogger<std::string, const Idea*> *seenIdeas, const Idea legislation) : 
	            mp_(mp), seenIdeas_(seenIdeas)
{
	std::cout << "You approach " << mp->getFirstName() << " " << mp->getLastName() << " -- " << mp->getDescription() << std::endl;

	//Using windows.h
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	std::cout << mp->sayHello() << std::endl;

	std::string cmd;

	while (true) {
		std::cout << "Command: ";
		std::string cmd;
		std::getline(std::cin, cmd);

		if (cmd == "Ask for support" || cmd == "support") {
			std::string output = mp->getFirstName() + " " + mp->getLastName() + ": " + mp->getOpinion(&legislation);
			std::cout << output << std::endl;
		}
		else if (cmd == "Suggest idea" || cmd == "suggest") {
			suggestIdea();
		}
		else if (cmd == "Current ideas" || cmd == "ideas") {
			getCurrentIdeas();
		}
		else if (cmd == "Leave" || cmd == "quit" || cmd =="q") {
			endConversation();
			return;
		}
		else if (cmd == "Help" || cmd == "help") {
			getHelp();
		}
		else {
			std::cout << "Command not recognised." << std::endl;
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
	output += '\t' + std::to_string(seenIdeas_->size()) + ") Never mind\nCommand: ";

	while (true) {
		std::cout << output;
		std::string ans;
		std::getline(std::cin, ans);
		std::stringstream stream(ans);
		int num;
		if (stream >> num) {
			if (num == seenIdeas_->size()) {
				return;
			}
			else if (num >= 0 && num < seenIdeas_->size()) {
				const Idea* suggIdea = ideaList[num];
				std::cout << mp_->getOpinion(suggIdea) << std::endl;
				return;
			}
		}
		std::cout << "Command not recognised." << std::endl;
	}
}

void Conversation::getCurrentIdeas() {
	const std::vector<const Idea*> ideaList = mp_->getListOfIdeas();
	std::string currIdeasOutput = mp_->getFirstName() + " " + mp_->getLastName() + ": The ideas I currently like are\n";

	for (std::vector<const Idea*>::const_iterator it = ideaList.begin(); it != ideaList.end(); ++it) {
		currIdeasOutput += '\t' + (*it)->getName() + '\n';
		seenIdeas_->add((*it)->getName(),*it);
	}

	std::cout << currIdeasOutput;
}

void Conversation::endConversation() {
	std::string output = mp_->getFirstName() + " " + mp_->getLastName() + ": " + mp_->sayGoodbye();
	std::cout << output << std::endl;
	//Using windows.h
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Conversation::getHelp() {
	std::string help = "Command options are:\n\tAsk for support\n\tSuggest idea\n\tCurrent ideas\n\tLeave";
	std::cout << help << std::endl;
}

Conversation::~Conversation()
{
}
