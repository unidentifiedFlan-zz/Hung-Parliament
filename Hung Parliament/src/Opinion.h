#pragma once
#include "stdafx.h"
#include "characteristics.h"

class Opinion {

	// ID is used to ensure copies still identify as the same opinion. It is
	// assigned only in the constructors; the copy constructor and assignment
	// operator will copy the original's ID
	Opinion *id_;

	std::string text_;
	Characteristics characs_;
public:
	Opinion(std::string opText, Characteristics opCharacs) : id_(this), text_(opText), characs_(opCharacs){}

	bool operator ==(const Opinion &opinion) const {
		return id_ == opinion.id_;
	}

	bool operator !=(const Opinion &opinion) const {
		return id_ != opinion.id_;
	}

	bool operator <(const Opinion &opinion) const {
		return id_ < opinion.id_;
	}

	bool operator >(const Opinion &opinion) const {
		return id_ > opinion.id_;
	}

	std::string get() const { return text_; }
	Characteristics getCharacteristics() const { return characs_; }
};