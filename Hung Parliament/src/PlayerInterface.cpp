#include "PlayerInterface.h"
#include "UserCommands.h"

class Politician;

PlayerInterface::PlayerInterface(Whip *whip) : whip_(whip) {
}

void PlayerInterface::waitForCommand(bool *quit) {

	Output::general(introduction());

	std::string cmd;

	while (!(*quit)) {
		std::getline(std::cin, cmd);
		applyCommand(cmd, quit);
	}
}

std::string PlayerInterface::introduction() {
	std::string output = "";
	return output;
}


void PlayerInterface::applyCommand(std::string &cmd, bool *quit) {

	if (userCommands::findMP(cmd)) {
		startConversation();
	}
	else if (userCommands::quit(cmd)) {
		confirmQuit(quit);
	}
	else {
		getInformation(cmd);
	}
}

void PlayerInterface::getInformation(std::string &cmd) {

	if (userCommands::getAdvice(cmd)) {
		Output::whip(whip_->getAdvice());

	}
	else if (userCommands::getLegislationInformation(cmd)) {
		Output::whip(whip_->describeLegislation());

	}
	else if (cmd == "Trending ideas") {
		Output::whip("To do...");
	}
	else if (userCommands::getStatistics(cmd)) {
		getStatistics();
	}
	else if (userCommands::help(cmd)) {
		Output::general(getHelp());
	}
	else {
		Output::general("Command not recognised.");
	}
}

void PlayerInterface::startConversation() {

	Output::whip("Who would you like to have a friendly chat with?");
	std::string mpName;

	std::getline(std::cin, mpName);

	Politician *mp = whip_->findMP(mpName);
	if (mp != nullptr) {
		speakToMP(mp);
	}
	else {
		Output::whip("There doesn't appear to be an MP with that name.");
	}
}

void PlayerInterface::speakToMP(Politician* mp) {

	if (Conversation::politicianAvailable(mp)) {
		Conversation newConv(mp, &seenIdeas_, whip_->getLegislation());
	}
	else {
		Output::whip("That MP appears to be busy. Try again later.");
	}
}

void PlayerInterface::getStatistics() {

	while (true) {
		Output::whip("What kind of statistics would you like?");
		std::string cmd;
		std::getline(std::cin, cmd);

		if (userCommands::getOverview(cmd)) {
			Output::whip(whip_->getStatistics());
		}
		else if (userCommands::idea(cmd)) {
			getIdeaDetails();
		}
		else if (userCommands::mp(cmd)) {
			getMPDetails();
		}
		else if (userCommands::help(cmd)) {
			Output::whip("The options are:\n\tGeneral overview\n\tIdea statistics\n\tMP statistics");
		}
		else if (userCommands::quit(cmd)) {
			Output::whip("Yes, that's enough of statistics. Let's get to action!");
			return;
		}
		else {
			Output::general("Command not recognised.");
		}
	}

}

void PlayerInterface::getIdeaDetails() {

	while (true) {
		Output::whip("Which idea would you like information about?");
		std::string cmd;
		std::getline(std::cin, cmd);

		HistoryLogger<std::string, const Idea*>::Iterator ideaIt = seenIdeas_.find(cmd);

		if (ideaIt != seenIdeas_.end()) {
			Output::whip(whip_->getIdeaDetails(ideaIt->second));
			return;
		}
		else if (userCommands::getListOfIdeas(cmd)) {
			if (seenIdeas_.size() == 0) {
				Output::general("You haven't heard any ideas yet.");
			}
			for (HistoryLogger<std::string, const Idea*>::Iterator it = seenIdeas_.begin(); it != seenIdeas_.end(); ++it) {
				Output::general((it->second)->getName());
			}
		}
		else if (userCommands::quit(cmd)) {
			return;
		}
		else if (userCommands::help(cmd)) {
			Output::whip("The options are:\n\tGive an idea name\n\tList ideas\n\tquit");
		}
		else {
			Output::general("Idea or command not recognised.");
		}
	}
}

void PlayerInterface::getMPDetails() {

	while (true) {
		Output::whip("Which MP would you like information about?");
		std::string cmd;
		std::getline(std::cin, cmd);

		Politician* mp = whip_->findMP(cmd);

		if (mp != nullptr) {
			Output::whip(whip_->getMPDetails(mp));
			return;
		}
		else if (userCommands::quit(cmd)) {
			return;
		}
		else if (userCommands::help(cmd)) {
			Output::whip("The options are:\n\tGive an MP's name\n\tquit");
		}
		else {
			Output::general("MP or command not recognised.");
		}
	}
}

std::string PlayerInterface::getHelp() {

	std::string output = "Command options are: ";
	output += "\n\tFind mp";
	output += "\n\tGet advice";
	output += "\n\tLegislation info";
	output += "\n\tTrending ideas";
	output += "\n\tGet stats";
	output += "\n\tQuit";

	return output;
}

bool PlayerInterface::confirmQuit(bool *quit) {
	Output::general("Are you sure you want to quit? (y/n)");

	while (true) {
		std::string ans;
		std::getline(std::cin, ans);
		if (ans == "y") {
			*quit = true;
			break;
		}
		else if (ans == "n") {
			Output::whip("Let's get back to it. There's no time to lose!");
			break;
		}
		else {
			Output::general("Command not recognised. Please enter y or n.");
		}
	}

	return quit;
}

PlayerInterface::~PlayerInterface()
{
}
