#include "SampleGame.h"

#include <iostream>

int main()
{
	std::cout << "WELCOME!" << std::endl;
	std::cout << "To toggle light fade in/out press F" << std::endl;
	std::cout << "To toggle light colour change press C" << std::endl;
	std::cout << "To toggle light rotation press L" << std::endl;
	std::cout << "To toggle model object rotation press O" << std::endl;
	std::cout << "To toggle triplanar shader press S" << std::endl;

	std::cout << "Press enter to start !" << std::endl;
	std::cin >> std::noskipws >> std::string();

	SampleGame game;
	game.start();

	std::cout << "The End" << std::endl;
	return 0;
}