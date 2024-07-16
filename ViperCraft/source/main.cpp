#include <ViperCraft/ViperCraft.h>

#include <iostream>

int main()
{
	ViperCraft::ViperCraftErrorCode ec;
	ViperCraft::ViperCraft::CreateGame(ec);

	if (ec != ViperCraft::ViperCraftErrorCode::Success)
	{
		std::cout << "Failed to initialize game.\n";
		return -1;
	}

	ViperCraft::ViperCraft::GetInstance()->run();
	return 0;
}