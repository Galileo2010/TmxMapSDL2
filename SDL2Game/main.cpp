#include <iostream>
#include <string>
#include <tmxlite/Map.hpp>

#include "cc.h"

int main(int argc, char* argv[])
{
	tmx::Map map;
	;
	if (!map.load("../maps/2.5d-simple.tmx")) {
		std::cerr << "Failed to open map !" << std::endl;
		return 0;
	}
	std::cout << "Map was parsed successful..." << std::endl;

	try {
		cc::Game game("hello", 800, 600);

		game.execute();
	}
	catch (cc::Exception ex) {
		cc::Logger::error(ex.getError().c_str());
		return 1;
	}
	return 0;
}
