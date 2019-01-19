#include "Output.h"



Output::Output()
{
}

std::string Output::command() {
	std::string output = "\rCommand: ";
	std::cout << output;

	return output;
}

std::string Output::general(std::string output) {

	std::cout << "\r" + output << std::endl;
	command();
	return output;
}

std::string Output::politician(std::string output, std::string name) {

	output = name + ": " + output;
	general(output);

	return output;
}

std::string Output::whip(std::string output) {

	output = "Whip: " + output;
	general(output);

	return output;
}

std::string Output::whipEvent(std::string output) {

	//Using windows.h
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO buffInfo;

	GetConsoleScreenBufferInfo(handle, &buffInfo);
	WORD origAttr = buffInfo.wAttributes;
	SetConsoleTextAttribute(handle, 4);

	output = "Whip: " + output;
	general(output);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), origAttr);
	command();

	return output;
}

void Output::switchToConversation() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	command();
}

void Output::switchToMainInterface() {
	//Using windows.h
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	command();
}

Output::~Output()
{
}
