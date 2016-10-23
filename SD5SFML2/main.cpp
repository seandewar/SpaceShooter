#include <iostream>

#include "Game.h"


int main()
{
	std::cout << "main() ---PROGRAM MAIN ENTRY POINT---" << std::endl;

	Game::Run();

	std::cout << "main() ---PROGRAM MAIN TERMINATION POINT---" << std::endl;
	return 0;
}