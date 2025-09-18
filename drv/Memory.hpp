#pragma once
#include <cstdlib>
#include <ctime>
#include "Misc.hpp"

namespace D
{
	void _Init();
}
void _Init() {
	srand(static_cast<unsigned>(time(nullptr)));
}

