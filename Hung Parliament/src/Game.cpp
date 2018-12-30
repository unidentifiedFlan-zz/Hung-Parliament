
#include "stdafx.h"
#include <thread>

#include "game.h"
#include "UserCommands.h"
#include "MPIsingModel.h"
#include "Parliament.h"
#include "Whip.h"

game::game()
{
	bool quit = false;

	MPIsingModel mpNetwork(1);
	Parliament parliament(20, &mpNetwork);

	PoliticianLists lists = parliament.createPoliticianLists();
	Whip whip(&parliament, lists);

	parliament.addListener(&whip);

	userCommands userComm(&whip);
	std::thread UIThread(&userCommands::waitForCommand, userComm, &quit);
	std::thread networkThread(&MPIsingModel::runDynamics, mpNetwork, &quit);
	
	while (!quit) {}

	networkThread.join();
	UIThread.join();
}

game::~game()
{
}
