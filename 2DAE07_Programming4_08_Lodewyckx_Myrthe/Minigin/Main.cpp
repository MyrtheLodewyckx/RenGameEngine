#include "MiniginPCH.h"
#include <steam_api.h>
#include "Achivements.h"

#ifdef _WIN64
#pragma comment(lib, "win64/steam_api64")
#else
#pragma comment(lib, "steam_api")
#endif



#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"

int main(int, char* []) {
if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
else
{
	std::cout << "Successfully initialized steam." << std::endl;
	dae::SteamAchievements::GetInstance().g_SteamAchievements = new CSteamAchievements(dae::SteamAchievements::GetInstance().g_Achievements, 4);
}
	dae::Minigin engine;
	engine.Run();

	SteamAPI_Shutdown();
	return 0;
}