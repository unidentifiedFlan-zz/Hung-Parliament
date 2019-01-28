#include "pch.h"

#include "gtest/gtest.h"
#include "../Hung Parliament/src/Characteristics.h"
#include "../Hung Parliament/src/HistoryLogger.h"
#include "../Hung Parliament/src/Idea.h"
#include "../Hung Parliament/src/Conversation.h"

class ConversationTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		Characteristics::Characteristic charac("influence", 5);
		std::vector<Characteristics::Characteristic> characList({ charac });
		characs = new Characteristics(characList);
		Opinion op1("acceptIdea", *characs);

		Characteristics::Characteristic charac2("influence", 4);
		std::vector<Characteristics::Characteristic> characList2({ charac });
		Characteristics characs2(characList2);
		Opinion op2("rejectIdea", characs2);

		Opinions opList;
		opList.add(op1);
		opList.add(op2);
		
		idea = new Idea("idea", "idea", *characs, opList);
		legislation = new Idea("leg", "leg", *characs);
	}
	virtual void TearDown() {
		delete characs;
		delete idea;
		delete legislation;
	}

	Idea *idea;
	Characteristics *characs;
	HistoryLogger<std::string, Idea*> *histLog;
	Idea *legislation;
};

TEST_F(ConversationTest, suggestIdea) {	
	//Create MP who will accept idea and who would normally have accepting opinion
	//Politician mp1("mp1", "mp1", *characs);
	//Conversation conv1(&mp1, histLog, *legislation);
	
	//ASSERT_EQ("acceptIdea", conv1.suggestIdea(idea));

	//Create second mp who will accept idea but who is closer to reject opinion.
	//They should have accept opinion as they accept the opinion
//	Characteristics::Characteristic charac2("influence", 3);
	//std::vector<Characteristics::Characteristic> characList2({ charac2 });
	//Characteristics characs2(characList2);

//	Politician mp2("mp2", "mp2", characs2);
//	Conversation conv1(&mp2, histLog, *legislation);


	//Create third mp who will reject idea and who should have reject opinion
}
