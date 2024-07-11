#include <ViperCraft/ViperCraft.h>

#include <iostream>

int main()
{
	ViperCraft::ViperCraftErrorCode ec;
	ViperCraft::ViperCraft game(ec);

	if (ec != ViperCraft::ViperCraftErrorCode::Success)
	{
		std::cout << "Failed to initialize game.\n";
		return -1;
	}

	game.run();
	return 0;
}