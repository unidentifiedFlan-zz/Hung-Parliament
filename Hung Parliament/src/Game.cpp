
#include "stdafx.h"
#include <thread>

#include "game.h"
#include "PlayerInterface.h"
#include "DynamicNetwork.h"
#include "MPIsingModel.h"
#include "Parliament.h"
#include "Whip.h"

game::game()
{
	bool quit = false;
	const unsigned int numMPs = 100;

	MPIsingModel model;
	DynamicNetwork mpNetwork(1, model);
	Parliament parliament(numMPs, &mpNetwork);

	PoliticianLists lists = parliament.createPoliticianLists();

	Whip whip(&parliament, lists);

	parliament.addListener(&whip);

	PlayerInterface playerInterface(&whip);
	std::thread UIThread(&PlayerInterface::waitForCommand, playerInterface, &quit);
	std::thread networkThread(&DynamicNetwork::runDynamics, mpNetwork, &quit);
	
	while (!quit) {}

	networkThread.join();
	UIThread.join();
}

game::~game()
{
}
