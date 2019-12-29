
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "SYDEstdafx.h"
#include "TicTacToe.h"


using namespace std;
using namespace Gdiplus;
//INITIALIZING VARIABLES
int windowWidth = 40;
const int windowHeight = 20;
const string dir = "BrainFiles\\";
Settings config("EngineFiles\\Settings\\configSettings.sc");
ConsoleWindow window(windowHeight);
//DRAWING SETTINGS
BackgroundClass bgVars;
Characters charVars;
Artwork artVars;
//OTHER ASSETS
AssetsClass astVars;
//DECLARE CUSTOM ASSETS HERE
COORD start = { (SHORT)0, (SHORT)0 };
static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CustomAnimationAsset testAnimation;
//CHEATS
vector<string> cheatCodes;
static ULONG_PTR gdiplusToken;
static GdiplusStartupInput startupInput;
class AutoClicker : public SYDEWindowGame {
public:
	AutoClicker() { m_bg = CustomAsset(40, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg.bmp", 20, 20)); }
	virtual ~AutoClicker() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
private:
	CustomAsset m_bg;
	bool _autoClickOn = false;
};
int main()
{
	LPCWSTR title = L"AutoClickerProgram";
	SYDECredits::_GAMETITLE = "AutoClick";
	SYDECredits::_ORGANISATION = "Callum Hands \nIn Association With Freebee Games";
	//CONSOLE SETTINGS
	//SYDE ENGINE SETTINGS
	GdiplusStartup(&gdiplusToken, &startupInput, 0);
	SetConsoleTitleW(title);
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	SYDEGamePlay::initialize_window(hOut, window);
	for (int i = 0; i < windowWidth; i++)
	{
		for (int j = 0; j < windowHeight; j++)
		{
			window.setTextAtPoint(Vector2(i, j), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
		}
	}
	SYDEGamePlay::activate_bySplashscreen(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
	//GAMEPLAY

	AutoClicker m_TTT;

	while (true)
	{
		window = SYDEGamePlay::play_game(&m_TTT, start, hOut, window, windowWidth, windowHeight, deltaTime);
		window.writeConsole();
		SYDEFunctions::SYDESleep(30, SYDEDefaults::getDeltaTime());
	}
	system("cls");
	return NULL;

}

ConsoleWindow AutoClicker::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_bg.draw_asset(window, Vector2(0, 0));
	window.setTextAtPoint(Vector2(0, 19), "AutoClick - Press A To Toggle", BLACK_WHITE_BG);
	int x,y = 0;
	if (_autoClickOn)
	{
		window = m_bg.draw_asset(window, Vector2(0, 0));
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		//x = 0;
		x = cursorPos.x;
		//y = 0;
		y = cursorPos.y;
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	}
	if (SYDEKeyCode::get('A')._CompareState(KEYDOWN))
	{
		_autoClickOn = !_autoClickOn;
	}
	return window;
}
