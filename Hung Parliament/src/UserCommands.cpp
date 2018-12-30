#include "stdafx.h"
#include "UserCommands.h"
#include "Game.h"
#include "Conversation.h"

userCommands::userCommands(Whip* whip) : _whip(whip){
}

void userCommands::waitForCommand(bool *quit){

	std::string cmd;

	while (!(*quit)) {
		std::cout << "Command: ";
		std::getline(std::cin, cmd);
		applyCommand(cmd, quit);
	}
}


void userCommands::applyCommand(std::string &cmd, bool *quit) {

	if (findMP(cmd)) {
		startConversation();
	}
	else if (requestQuit(cmd)) {
		confirmQuit(quit);
	}
	else {
		getInformation(cmd);
	}
}

void userCommands::getInformation(std::string &cmd) {

	if (requestAdvice(cmd)) {
		std::cout << _whip->getAdvice() << std::endl;
		
	}
	else if (cmd == "Legislation info") {
		std::cout << _whip->describeLegislation() << std::endl;
		
	}
	else if (cmd == "Trending ideas") {
		std::cout << "To do..." << std::endl;
	}
	else if (requestStatistics(cmd)) {
		getStatistics();
	}
	else if (requestHelp(cmd)) {
		getHelp();
	}
	else {
		std::cout << "Command not recognised." << std::endl;
	}
}

bool userCommands::findMP(std::string &cmd) {
	return (cmd ==  "mp" ||
		cmd == "Find mp" ||
		cmd == "Find MP" ||
		cmd == "find mp" ||
		cmd == "find MP");
}

bool userCommands::requestAdvice(std::string &cmd) {
	return (cmd == "advice" ||
		cmd == "get advice" ||
		cmd == "Get advice");
}

bool userCommands::requestStatistics(std::string &cmd) {
	return (cmd == "stats" ||
		cmd == "Get statistics" ||
		cmd == "get stats" ||
		cmd == "statistics" ||
		cmd == "Get stats" ||
		cmd == "get stats");
}

bool userCommands::requestQuit(std::string &cmd) {
	return (cmd == "Quit" || cmd == "quit" || cmd == "q");
}

bool userCommands::requestHelp(std::string &cmd) {
	return (cmd == "Help" || cmd == "help" || cmd == "h");
}

void userCommands::startConversation() {

	std::cout << "Whip: Who would you like to have a friendly chat with?\nCommand: ";
	std::string mpName;

	std::getline(std::cin, mpName);

	Politician *mp = _whip->findMP(mpName);
	if (mp != nullptr) {
		speakToMP(mp);
	}
	else {
		std::cout << "Whip: There doesn't appear to be an MP with that name." << std::endl;
	}
}

void userCommands::confirmQuit(bool *quit) {
	std::cout << "Are you sure you want to quit? (y/n)" << std::endl;

	while (true) {
		std::cout << "Command: ";
		std::string ans;
		std::getline(std::cin, ans);
		if (ans == "y") {
			*quit = true;
			break;
		}
		else if (ans == "n") {
			break;
		}
		else {
			std::cout << "Command not recognised. Please enter y or n." << std::endl;
		}
	}
}

void userCommands::speakToMP(Politician* mp ) {
	 
	if (mp->isAvailable()) {
		Conversation newConv(mp, &seenIdeas_, _whip->getLegislation());
		mp->setAvailable();
	}
	else {
		std::cout << "Whip: That MP appears to be busy. Try again later." << std::endl;
	}
}

void userCommands::getStatistics() {

	while (true) {
		std::cout << "Whip: what kind of statistics would you like?\nCommand: ";
		std::string cmd;
		std::getline(std::cin, cmd);

		if (cmd == "General overview" || cmd == "general" || cmd == "overview") {
			std::cout << _whip->getStatistics() << std::endl;
			return;
		}
		else if (cmd == "idea" || cmd == "Idea statistics") {
			getIdeaDetails();
			return;
		}
		else if (cmd == "mp" || cmd == "MP statistics") {
			getMPDetails();
			return;
		}
		else if (requestHelp(cmd)) {
			std::string output = "The options are:\n\tGeneral overview\n\tIdea statistics\n\tMP statistics";
			std::cout << output << std::endl;
		}
		else {
			std::cout << "Command not recognised." << std::endl;
		}
	}

}

void userCommands::getIdeaDetails() {

	while (true) {
		std::cout << "Whip: Which idea would you like information about?\nCommand: ";
		std::string cmd;
		std::getline(std::cin, cmd);

		HistoryLogger<std::string, const Idea*>::Iterator idea = seenIdeas_.find(cmd);

		if (idea != seenIdeas_.end()) {
			Characteristics characs = idea->second->getCharacteristics();
			std::cout << idea->second->getName() + " has the following characteristics:\n";
			std::cout << characs << "Command: ";
			return;
		}
		else if (cmd == "List ideas" || cmd == "list") {
			if (seenIdeas_.size() == 0) {
				std::cout << "You haven't heard any ideas yet." << std::endl;
			}
			for (HistoryLogger<std::string, const Idea*>::Iterator it = seenIdeas_.begin(); it != seenIdeas_.end(); ++it) {
				std::cout << (it->second)->getName() + "\n";
			}
		}
		else if (cmd == "q" || cmd == "quit") {
			return;
		}
		else if (requestHelp(cmd)) {
			std::string output = "Whip: The options are:\n\tGive an idea name\n\tList ideas\n\tquit";
			std::cout << output << std::endl;
		}
		else {
			std::cout << "Idea or command not recognised." << std::endl;
		}
	}
}

void userCommands::getMPDetails() {

	while (true) {
		std::cout << "Whip: Which MP would you like information about?\nCommand: ";
		std::string cmd;
		std::getline(std::cin, cmd);

		Politician* mp = _whip->findMP(cmd);

		if (mp != nullptr) {
			Characteristics characs = mp->getCharacteristics();
			std::cout << mp->getFirstName() + " " + mp->getLastName() + " has the following characteristics:\n";
			std::cout << characs << std::endl;
			return;
		}
		else if (cmd == "q" || cmd == "quit") {
			return;
		}
		else if (requestHelp(cmd)) {
			std::string output = "Whip: The options are:\n\tGive an MP's name\n\tquit";
			std::cout << output << std::endl;
		}
		else {
			std::cout << "MP or command not recognised." << std::endl;
		}
	}
}

void userCommands::getHelp() {

	std::cout << "Command options are: " << std::endl;
	std::cout << '\t' << "Find mp" << std::endl;
	std::cout << '\t' << "Get advice" << std::endl;
	std::cout << '\t' << "Legislation info" << std::endl;
	std::cout << '\t' << "Trending ideas" << std::endl;
	std::cout << '\t' << "Get stats" << std::endl;
	std::cout << '\t' << "Quit" << std::endl;
}

userCommands::~userCommands()
{
}
