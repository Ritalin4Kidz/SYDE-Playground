
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "SYDEstdafx.h"
#include "TicTacToe.h"
#include <fstream>
#include <istream>
#include <sstream>


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
	AutoClicker() { m_bg = CustomAsset(40, 20, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg.bmp", 20, 20)); LoadSettings(); }
	virtual ~AutoClicker() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
private:

	void LoadSettings();
	std::vector<std::string> Split(std::string a_String, char splitter);

	CustomAsset m_bg;
	bool _autoClickOn = false;
	int CLICK_DELAY = 0;
	float _TIME_PASSED = 0.0f;
	int clicks = 0;

	//KEYPRESSES
	char _ClickCharacter = 'A';
	char _INCREASE_CLICK_DELAY_KEYPRESS = 'W';
	char _DECREASE_CLICK_DELAY_KEYPRESS = 'S';

	std::string _CLICK_CHAR_STR = "Toggle AutoClick : A";
	std::string _INCREASE_CHAR_STR = "Decrease Click Delay: W";
	std::string _DECREASE_CHAR_STR = "Decrease Click Delay: S";

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
	//window.setTextAtPoint(Vector2(0, 15), "Click Delay: " + std::to_string(clicks), BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 16), "Click Delay: " + std::to_string(CLICK_DELAY), BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 17), _INCREASE_CHAR_STR, BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 18), _DECREASE_CHAR_STR, BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 19), _CLICK_CHAR_STR, BLACK_WHITE_BG);
	int x,y = 0;
	if (_autoClickOn)
	{
		if (CLICK_DELAY == 0 || _TIME_PASSED > CLICK_DELAY)
		{
			window = m_bg.draw_asset(window, Vector2(0, 0));
			POINT cursorPos;
			GetCursorPos(&cursorPos);
			//x = 0;
			x = cursorPos.x;
			//y = 0;
			y = cursorPos.y;
			mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
			_TIME_PASSED = 0;
			//clicks++;
		}
		if (CLICK_DELAY > 0)
		{
			_TIME_PASSED += SYDEDefaults::getDeltaTime() * 1000;
		}
	}
	if (SYDEKeyCode::get(_ClickCharacter)._CompareState(KEYDOWN))
	{
		_autoClickOn = !_autoClickOn;
	}
	if (SYDEKeyCode::get(_INCREASE_CLICK_DELAY_KEYPRESS)._CompareState(KEYDOWN) && CLICK_DELAY < 2000)
	{
		CLICK_DELAY += 100;
	}
	if (SYDEKeyCode::get(_DECREASE_CLICK_DELAY_KEYPRESS)._CompareState(KEYDOWN) && CLICK_DELAY > 0)
	{
		CLICK_DELAY -= 100;
	}
	return window;
}

void AutoClicker::LoadSettings()
{
	std::ifstream File("EngineFiles\\Settings\\clickerSettings.sc", std::ios::binary | std::ios::in);
	if (File.is_open())
	{
		std::string line;
		std::vector<std::string> FileLines;
		while (getline(File, line, '\n'))
		{
			FileLines = Split(line, ':');
			FileLines[1] = FileLines[1].substr(0, 1);
			if (FileLines[0] == "TOGGLE_AUTOCLICK_KEYPRESS")
			{
				std::istringstream(FileLines[1]) >> _ClickCharacter;
				_CLICK_CHAR_STR = "Toggle AutoClick: " + FileLines[1];
			}
			if (FileLines[0] == "INCREASE_DELAY_KEYPRESS")
			{
				std::istringstream(FileLines[1]) >> _INCREASE_CLICK_DELAY_KEYPRESS;
				_INCREASE_CHAR_STR = "Increase Click Delay: " + FileLines[1];
			}
			if (FileLines[0] == "DECREASE_DELAY_KEYPRESS")
			{
				std::istringstream(FileLines[1]) >> _DECREASE_CLICK_DELAY_KEYPRESS;
				_DECREASE_CHAR_STR = "Decrease Click Delay: " + FileLines[1];
			}
		}
	}
}

std::vector<std::string> AutoClicker::Split(std::string a_String, char splitter)
{
	int arraySize = 1;
	for (int i = 0; i < a_String.length(); i++)
	{
		if (a_String[i] == splitter)
		{
			arraySize++;
		}
	}
	std::vector<std::string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < a_String.length(); i++)
		{
			if (a_String[i] == splitter)
			{
				splitString[arrayNo] = a_String.substr(0, i);
				a_String = a_String.substr(i + 1, a_String.length() - i);
				arrayNo++;
				break;
			}
		}
	}
	splitString[arraySize - 1] = a_String;
	return splitString;
}
