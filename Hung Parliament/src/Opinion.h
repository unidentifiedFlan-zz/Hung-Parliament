#pragma once
#include "stdafx.h"
#include "characteristics.h"

class Opinion {
	std::string text;
	Characteristics characs;
public:
	Opinion(std::string opText, Characteristics opCharacs) : text(opText), characs(opCharacs){}
	std::string getOpinion() { return text; }
	Characteristics getCharacteristics() { return characs; }
};