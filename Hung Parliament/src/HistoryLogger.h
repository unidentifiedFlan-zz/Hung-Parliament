#pragma once

template<class T, class U>
class HistoryLogger
{
	std::map<T, U> history;
public:

	typename typedef std::map<T, U>::iterator Iterator;

	HistoryLogger() {

	}

	U add(const T item, const U value) {
		history.emplace(item, value);
		return value;
	}

	bool update(const T item, const U value) {
		typename std::map<T, U>::iterator it = history.find(item);

		if (it != history.end()) {
			it->second = value;
			return true;
		}
		else {
			return false;
		}
	}

	bool remove(const T item) {
		typename std::map<T, U>::iterator it = history.find(item);

		if (it != history.end()) {
			history.erase(item);
			return true;
		}
		else {
			return false;
		}
	}

	int size() {
		return history.size();
	}

	bool exists(const T item) {
		typename std::map<T, U>::iterator it = history.find(item);

		if (it != history.end()) {
			return true;
		}
		else {
			return false;
		}
	}

	Iterator find(const T item) {
		typename std::map<T, U>::iterator it = history.find(item);
		if (it != history.end()) {
			return it;
		}
		
		return history.end();
	}

	void clear() {
		history.clear();
	}

	Iterator begin() {
		return history.begin();
	}

	Iterator end() {
		return history.end();
	}

	~HistoryLogger() {}
};

