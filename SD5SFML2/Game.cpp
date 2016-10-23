#include "Game.h"


void Game::Run()
{
	if(running)
		return;

	Load();

	running = true;

	//Main game loop
	while(!exiting)
	{
		GameLoop();
	}

	Unload();
	window.close();
	running = false;
}


void Game::Load()
{
	window.create(sf::VideoMode(800, 600), "SD5 Space Game");
	srand(time(NULL));

	//TODO LOAD IN A NEATER WAY OR SOMETHING IUNNO LIKE AN ASSET LOADER OR SOMETHING LOL
	mainFont.loadFromFile("arial.ttf");
	courierFont.loadFromFile("courbd.ttf");

#ifdef _DEBUG
	debugOverlayStatePntr = new DebugOverlayState(&stateManager, mainFont);
	stateManager.PushStateBack(debugOverlayStatePntr);
#endif

	gameStatePntr = new GameState(courierFont);

#ifdef _DEBUG
	debugOverlayStatePntr->SetGameState(gameStatePntr);
#endif

	stateManager.PushStateBack(gameStatePntr);
}


void Game::Unload()
{
#ifdef _DEBUG
	debugOverlayStatePntr->ResetGameState();
#endif
}


void Game::GameLoop()
{
	if(!running)
		return;
	
	sf::Event currentEvent;

	//Handle all events in queue before proceeding.
	while(window.pollEvent(currentEvent))
	{
		switch(currentEvent.type)
		{
		case sf::Event::Closed:
			exiting = true;
			break;
		}
	}

	Update();
	Draw();
}


void Game::Update()
{
	if(!running)
		return;

	elapsed = clock.getElapsedTime();

	stateManager.Update(elapsed, ((double)elapsed.asMicroseconds() - (double)lastElapsed.asMicroseconds())/1000);

	lastElapsed = elapsed;
}


void Game::Draw()
{
	if(!running)
		return;

	window.clear();
		stateManager.Draw(clock.getElapsedTime(), window);
	window.display();
}


bool Game::IsRunning()
{
	return running;
}


bool Game::IsExiting()
{
	return exiting;
}


bool Game::running = false;
bool Game::exiting = false;

sf::RenderWindow Game::window;
sf::Clock Game::clock;
sf::Time Game::elapsed;
sf::Time Game::lastElapsed;

StateManager Game::stateManager(clock.getElapsedTime());

DebugOverlayState* Game::debugOverlayStatePntr = nullptr;
GameState* Game::gameStatePntr = nullptr;

sf::Font Game::mainFont;
sf::Font Game::courierFont;