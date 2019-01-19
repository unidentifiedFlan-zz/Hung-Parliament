
#include "stdafx.h"
#include <thread>

#include "game.h"
#include "PlayerInterface.h"
#include "MPIsingModel.h"
#include "Parliament.h"
#include "Whip.h"

game::game()
{
	bool quit = false;

	MPIsingModel mpNetwork(1);
	Parliament parliament(100, &mpNetwork);

	PoliticianLists lists = parliament.createPoliticianLists();
	Whip whip(&parliament, lists);

	parliament.addListener(&whip);

	PlayerInterface playerInterface(&whip);
	std::thread UIThread(&PlayerInterface::waitForCommand, playerInterface, &quit);
	std::thread networkThread(&MPIsingModel::runDynamics, mpNetwork, &quit);
	
	while (!quit) {}

	networkThread.join();
	UIThread.join();
}

game::~game()
{
}
