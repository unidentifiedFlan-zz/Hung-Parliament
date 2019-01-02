#include "stdafx.h"
#include "UserCommands.h"
#include "Game.h"
#include "Conversation.h"

userCommands::userCommands(Whip* whip) : _whip(whip){
}

void userCommands::waitForCommand(bool *quit){

	streamOutput(introduction());

	std::string cmd;

	while (!(*quit)) {
		std::getline(std::cin, cmd);
		applyCommand(cmd, quit);
	}
}

std::string userCommands::introduction() {
	std::string output = "";
	return output;
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
		streamWhip(_whip->getAdvice());
		
	}
	else if (cmd == "Legislation info") {
		streamWhip(_whip->describeLegislation());
		
	}
	else if (cmd == "Trending ideas") {
		streamWhip("To do...");
	}
	else if (requestStatistics(cmd)) {
		getStatistics();
	}
	else if (requestHelp(cmd)) {
		streamOutput(getHelp());
	}
	else {
		streamOutput("Command not recognised.");
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

	streamWhip("Who would you like to have a friendly chat with?");
	std::string mpName;

	std::getline(std::cin, mpName);

	Politician *mp = _whip->findMP(mpName);
	if (mp != nullptr) {
		speakToMP(mp);
	}
	else {
		streamWhip("There doesn't appear to be an MP with that name.");
	}
}

void userCommands::confirmQuit(bool *quit) {
	streamOutput("Are you sure you want to quit? (y/n)");

	while (true) {
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
			streamOutput("Command not recognised. Please enter y or n.");
		}
	}
}

void userCommands::speakToMP(Politician* mp ) {
	 
	if (mp->isAvailable()) {
		Conversation newConv(mp, &seenIdeas_, _whip->getLegislation());
		mp->setAvailable();
	}
	else {
		streamWhip("That MP appears to be busy. Try again later.");
	}
}

void userCommands::getStatistics() {

	while (true) {
		streamWhip("What kind of statistics would you like?");
		std::string cmd;
		std::getline(std::cin, cmd);

		if (cmd == "General overview" || cmd == "general" || cmd == "overview") {
			streamWhip(_whip->getStatistics());
		}
		else if (cmd == "idea" || cmd == "Idea statistics") {
			getIdeaDetails();
		}
		else if (cmd == "mp" || cmd == "MP statistics") {
			getMPDetails();
		}
		else if (requestHelp(cmd)) {
			streamWhip("The options are:\n\tGeneral overview\n\tIdea statistics\n\tMP statistics");
		}
		else if (requestQuit(cmd)) {
			return;
		}
		else {
			streamOutput("Command not recognised.");
		}
	}

}

void userCommands::getIdeaDetails() {

	while (true) {
		streamWhip("Which idea would you like information about?");
		std::string cmd;
		std::getline(std::cin, cmd);

		HistoryLogger<std::string, const Idea*>::Iterator idea = seenIdeas_.find(cmd);

		if (idea != seenIdeas_.end()) {
			streamWhip(idea->second->getName() + " has the following characteristics:");
			streamCharacteristics(idea->second->getCharacteristics());
			return;
		}
		else if (cmd == "List ideas" || cmd == "list") {
			if (seenIdeas_.size() == 0) {
				streamOutput("You haven't heard any ideas yet.");
			}
			for (HistoryLogger<std::string, const Idea*>::Iterator it = seenIdeas_.begin(); it != seenIdeas_.end(); ++it) {
				streamOutput((it->second)->getName());
			}
		}
		else if (requestQuit(cmd)) {
			return;
		}
		else if (requestHelp(cmd)) {
			streamWhip("The options are:\n\tGive an idea name\n\tList ideas\n\tquit");
		}
		else {
			streamOutput("Idea or command not recognised.");
		}
	}
}

void userCommands::getMPDetails() {

	while (true) {
		streamWhip("Which MP would you like information about?");
		std::string cmd;
		std::getline(std::cin, cmd);

		Politician* mp = _whip->findMP(cmd);

		if (mp != nullptr) {
			streamWhip(mp->getFirstName() + " " + mp->getLastName() + " has the following characteristics:");
			streamCharacteristics(mp->getCharacteristics());
			return;
		}
		else if (requestQuit(cmd)) {
			return;
		}
		else if (requestHelp(cmd)) {
			streamWhip("The options are:\n\tGive an MP's name\n\tquit");
		}
		else {
			streamOutput("MP or command not recognised.");
		}
	}
}

std::string userCommands::getHelp() {

	std::string output = "Command options are: ";
	output += "\n\tFind mp";
	output += "\n\tGet advice";
	output += "\n\tLegislation info";
	output += "\n\tTrending ideas";
	output += "\n\tGet stats";
	output += "\n\tQuit";

	return output;
}

std::string userCommands::streamWhip(std::string output) {

	output = "Whip: " + output;
	streamOutput(output);

	return output;
}

std::string userCommands::streamOutput(std::string output) {

	std::cout << "\r" + output << std::endl;
	streamCommand();

	return output;
}

std::string userCommands::streamCommand() {
	std::string output = "\rCommand: ";
	std::cout << output;

	return output;
}

void userCommands::streamCharacteristics(Characteristics characs) {

	std::cout << "\r" << characs << std::endl;
	streamCommand();
}

userCommands::~userCommands()
{
}
