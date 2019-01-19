#include "stdafx.h"
#include "UserCommands.h"

userCommands::userCommands(){
}

bool userCommands::mp(std::string &cmd) {
	return cmd == "mp" ||
		cmd == "MP";
}
bool userCommands::findMP(std::string &cmd) {
	return (mp(cmd) ||
		cmd == "Find mp" ||
		cmd == "Find MP" ||
		cmd == "find mp" ||
		cmd == "find MP");
}

bool userCommands::getAdvice(std::string &cmd) {
	return (cmd == "advice" ||
		cmd == "Advice" ||
		cmd == "get advice" ||
		cmd == "Get advice" ||
		cmd == "Get Advice" ||
		cmd == "get Advice");
}

bool userCommands::getLegislationInformation(std::string &cmd) {
	return cmd == "legislation information" ||
		cmd == "Legislation information" ||
		cmd == "legislation Information" ||
		cmd == "Legislation Information" ||
		cmd == "legislation" ||
		cmd == "Legislation" ||
		cmd == "Legislation Info" ||
		cmd == "legislation info" ||
		cmd == "legislation Info" ||
		cmd == "Legislation info";
}

bool userCommands::getStatistics(std::string &cmd) {
	return (cmd == "stats" ||
		cmd == "Get statistics" ||
		cmd == "get stats" ||
		cmd == "statistics" ||
		cmd == "Get stats" ||
		cmd == "get stats");
}

bool userCommands::getOverview(std::string &cmd) {
	return cmd == "General overview" ||
		cmd == "General Overview" ||
		cmd == "general" ||
		cmd == "General" ||
		cmd == "overview" ||
		cmd == "Overview";
}

bool userCommands::idea(std::string &cmd) {
	return cmd == "idea" ||
		cmd == "Idea";
}


bool userCommands::getSupport(std::string &cmd) {
	return cmd == "Ask for support" ||
		cmd == "ask for support" ||
		cmd == "support" ||
		cmd == "Support";
}

bool userCommands::suggestIdea(std::string &cmd) {
	return cmd == "Suggest idea" ||
		cmd == "Suggest Idea" ||
		cmd == "suggest" ||
		cmd == "Suggest" ||
		idea(cmd) ||
		cmd == "suggest Idea";
}

bool userCommands::getIdeas(std::string &cmd) {
	return cmd == "Current ideas" ||
		cmd == "current ideas" ||
		cmd == "ideas" ||
		cmd == "Ideas" ||
		cmd == "Current Ideas" ||
		cmd == "current Ideas";
}

bool userCommands::getListOfIdeas(std::string &cmd) {
	return cmd == "List ideas" ||
		cmd == "list";
}
bool userCommands::quit(std::string &cmd) {
	return (cmd == "Quit" ||
		cmd == "quit" ||
		cmd == "q");
}

bool userCommands::help(std::string &cmd) {
	return (cmd == "Help" ||
		cmd == "help" ||
		cmd == "h");
}


userCommands::~userCommands()
{
}
