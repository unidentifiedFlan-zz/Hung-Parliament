#pragma once
#include "stdafx.h"
#include "Politician.h"

class Politicians
{
	std::unordered_map<std::string, Politician> politicians_;
public:

	class Iterator {
		friend class Politicians;
		std::unordered_map<std::string, Politician>::iterator iter_;

		Iterator(std::unordered_map<std::string, Politician>::iterator &mapIter) : iter_(mapIter) {}

		Iterator& operator =(std::unordered_map<std::string, Politician>::iterator &mapIter) {
			iter_ = mapIter;
			return *this;
		}
	public:
		Iterator() {};
		Iterator operator ++() {
			++iter_;
			return *this;
		}

		Iterator operator ++(int) {
			iter_++;
			return *this;
		}

		Politician* operator *() {
			return &(iter_->second);
		}

		Politician* operator ->() {
			return &(iter_->second);
		}

		bool operator ==(const Iterator &otherIter) {
			return iter_ == otherIter.iter_;
		}

		bool operator !=(const Iterator &otherIter) {
			return iter_ != otherIter.iter_;
		}
	};

	Politicians();
	void add(Politician &politician);
	void remove(Politician &politician);
	void clear();
	bool includes(std::string name);
	Iterator find(std::string name);
	unsigned int numberOf() const;
	Iterator getFirst();
	Iterator getLast();
	~Politicians();
};

