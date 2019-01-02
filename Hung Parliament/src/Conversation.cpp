#include "stdafx.h"
#include "Conversation.h"
#include <sstream>

Conversation::Conversation(Politician *mp, HistoryLogger<std::string, const Idea*> *seenIdeas, const Idea legislation) : 
	            mp_(mp), seenIdeas_(seenIdeas), legislation_(legislation)
{
	streamOutput(introduction());

	//Using windows.h
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	streamMP(mp->sayHello());

	processCommands();
}


std::string Conversation::introduction() {
	std::string intro = "You approach " + mp_->getFirstName() + " " + mp_->getLastName() + " -- " + mp_->getDescription();

	return intro;
}


void Conversation::processCommands() {

	while (true) {
		std::string cmd;
		std::getline(std::cin, cmd);

		if (cmd == "Ask for support" || cmd == "support" || cmd == "Support") {
			streamMP(mp_->getOpinion(&legislation_));
		}
		else if (cmd == "Suggest idea" || cmd == "suggest" || cmd == "Suggest") {
			suggestIdea();
		}
		else if (cmd == "Current ideas" || cmd == "ideas" || cmd == "Ideas") {
			getCurrentIdeas();
		}
		else if (cmd == "Leave" || cmd == "quit" || cmd == "q") {
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
	output += '\t' + std::to_string(seenIdeas_->size()) + ") Never mind";

	while (true) {
		streamOutput(output);
		std::string ans;
		std::getline(std::cin, ans);
		std::stringstream stream(ans);
		int num;
		if (stream >> num) {
			if (num == seenIdeas_->size()) {
				streamCommand();
				return;
			}
			else if (num >= 0 && num < seenIdeas_->size()) {
				const Idea* suggIdea = ideaList[num];
				streamMP(mp_->getOpinion(suggIdea));
				return;
			}
		}
		streamOutput("Command not recognised.");
	}
}


void Conversation::getCurrentIdeas() {
	const std::vector<const Idea*> ideaList = mp_->getListOfIdeas();
	std::string currIdeasOutput = "The ideas I currently like are:";

	for (std::vector<const Idea*>::const_iterator it = ideaList.begin(); it != ideaList.end(); ++it) {
		currIdeasOutput += "\n\t" + (*it)->getName();
		seenIdeas_->add((*it)->getName(),*it);
	}

	streamOutput(currIdeasOutput);
}

void Conversation::endConversation() {
	std::string output = mp_->getFirstName() + " " + mp_->getLastName() + ": " + mp_->sayGoodbye();
	streamOutput(output);
	//Using windows.h
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	streamCommand();
}

void Conversation::getHelp() {
	std::string help = "Command options are:\n\tAsk for support\n\tSuggest idea\n\tCurrent ideas\n\tLeave";
	streamOutput(help);
}

std::string Conversation::streamMP(std::string output) {

	output = mp_->getFirstName() + " " + mp_->getLastName() + ": " + output;
	streamOutput(output);

	return output;
}

std::string Conversation::streamOutput(std::string output) {

	std::cout << "\r" + output << std::endl;
	streamCommand();
	return output;
}

std::string Conversation::streamCommand() {
	std::string output = "\rCommand: ";
	std::cout << output;

	return output;
}

Conversation::~Conversation()
{
}
