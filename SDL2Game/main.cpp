#include <iostream>
#include <string>
#include <tmxlite/Map.hpp>
#include "source/cc.h"

int main()
{
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
