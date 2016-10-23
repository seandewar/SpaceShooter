#include "StateManager.h"


StateManager::StateManager(sf::Time elapsedTime) :
	fps(0),
	framesCounted(0)
{
	std::cout << "StateManager::StateManager() Creating the state manager" << std::endl;

	ResetFrameRate(elapsedTime);
}


StateManager::~StateManager()
{
	std::cout << "StateManager::~StateManager() Erasing all states and destroying state manager" << std::endl;

	EraseAllStates();
}


void StateManager::EraseAllStates()
{
	std::cout << "StateManager::EraseAllStates() Erasing all states from states vector (total: " << states.size() << ")" << std::endl;

	//Unload all States.
	//This should also effectively clear the vector.
	stateVector::iterator it = states.begin();
	while(it != states.end())
	{
		it = EraseState(it);
	}
}


void StateManager::ResetFrameRate(sf::Time elapsedTime)
{
	timeNextFrame = elapsedTime + sf::milliseconds(1000);
	framesCounted = 0;
}


void StateManager::UpdateFrameRate(sf::Time elapsedTime)
{
	//If the next scheduled frame rate check is reached (1000 ms after last)
	if(elapsedTime >= timeNextFrame)
	{
		fps = framesCounted;
		ResetFrameRate(elapsedTime);
	}
}


void StateManager::Update(sf::Time elapsedTime, double timeDeltaMilliseconds)
{
	if(states.size() == 0)
		return;

	//Update all States.
	for(stateVector::reverse_iterator rit = states.rbegin(); rit != states.rend(); ++rit)
	{
		if((*rit)->update)
		{
			(*rit)->Update(elapsedTime, timeDeltaMilliseconds);
		}
	}

	UpdateFrameRate(elapsedTime);
}


void StateManager::Draw(sf::Time elapsedTime, sf::RenderWindow& window)
{
	if(states.size() == 0)
		return;

	//Draw all States from last state to first. (So the state at the beginning of the vector is drawn first)
	for(stateVector::reverse_iterator rit = states.rbegin(); rit != states.rend(); ++rit)
	{
		(*rit)->Draw(elapsedTime, window);
	}

	//Update frame counted.
	++framesCounted;
}


stateVector::const_iterator StateManager::InsertState(stateVector::const_iterator position, State* state)
{
	std::cout << "StateManager::InsertState() Adding state " << state->GetName() << std::endl;

	state->Load();

	return states.insert(position, state);
}


//Returns a valid iterator for the next element in the vector. Use this so iterator loops dont implode and explode and whatever.
stateVector::iterator StateManager::EraseState(stateVector::iterator position)
{
	std::cout << "StateManager::EraseState() Erasing state " << (*position)->GetName() << std::endl;

	(*position)->Unload();
	delete (*position);
	(*position) = nullptr;

	return states.erase(position);
}


stateVector::const_iterator StateManager::PushStateBack(State* state)
{
	return InsertState(states.end(), state);
}


void StateManager::PopStateBack()
{
	EraseState(states.end());
}


stateVector::size_type StateManager::GetStateCount() const
{
	return states.size();
}


int StateManager::GetFrameRate() const
{
	return fps;
}


//Gets the average draw time in milliseconds by dividing the amount of frames per second by 1000.
//This function will not return anything over 1000. The only case where it will is if the FPS value is 0 or lower, in which case 1001 will be returned (extremely low fps).
double StateManager::GetAverageDrawTimeMilliseconds() const
{
	if(fps > 0)
		return (1000/(double)fps);
	else
		return 1001;
}