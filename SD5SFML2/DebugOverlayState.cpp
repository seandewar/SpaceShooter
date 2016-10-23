#include "DebugOverlayState.h"


DebugOverlayState::DebugOverlayState(StateManager* stateManager, sf::Font& font) :
	State("DebugOverlayState"),
	stateManagerPntr(stateManager)
{
	std::cout << "DebugOverlayState::DebugOverlayState() Setting up" << std::endl;

	debugText.setFont(font);
	debugText.setString("Debug Overlay Text");
	debugText.setCharacterSize(14);

	ResetGameState();
}


DebugOverlayState::~DebugOverlayState()
{
	std::cout << "DebugOverlayState::~DebugOverlayState()" << std::endl;
}


void DebugOverlayState::SetGameState(GameState* gameState)
{
	gameStatePntr = gameState;
}


void DebugOverlayState::ResetGameState()
{
	gameStatePntr = nullptr;
}


void DebugOverlayState::Load()
{
	std::cout << "DebugOverlayState::Load()" << std::endl;
}


void DebugOverlayState::Unload()
{
	std::cout << "DebugOverlayState::Unload()" << std::endl;
}


void DebugOverlayState::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	std::stringstream debugTextBuf;
	debugTextBuf << "---Debug--- " << std::endl;

	if(elapsedTime.asMilliseconds() > 1000)
	{
		debugTextBuf << "FPS: " << stateManagerPntr->GetFrameRate() << std::endl;
		debugTextBuf << "Avg. Draw Time: " << stateManagerPntr->GetAverageDrawTimeMilliseconds() << "ms" << std::endl;
		debugTextBuf << "Elapsed Time: " << elapsedTime.asMilliseconds() << "ms" << std::endl;
		debugTextBuf << "Time Delta: " << timeDeltaMilliseconds << "ms" << std::endl;
		debugTextBuf << std::endl;

		if(gameStatePntr != nullptr)
		{
			debugTextBuf << "---Game---" << std::endl;
			debugTextBuf << "Entities Drawn: " << gameStatePntr->entityManager.GetLastDrawnEntities() << std::endl;
			debugTextBuf << "Entity Count: " << gameStatePntr->entityManager.GetEntityCount() << std::endl;

			debugTextBuf << std::endl << "Press F1 for EntityManager debug." << std::endl;
		}
	}
	else
	{
		debugTextBuf << "Waiting until 1 second elapsed time..." << std::endl;
	}

	debugText.setString(debugTextBuf.str());
}


void DebugOverlayState::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	window.draw(debugText);
}