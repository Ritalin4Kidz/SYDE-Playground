#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "SYDEstdafx.h"
#include "Dictionary.h"


using namespace std;
class TicTacToePiece {
public:
	TicTacToePiece(int val, Vector2 pos) { m_Value = val; m_BoardPos = pos; }
	virtual ~TicTacToePiece() {}

	int getValue() { return m_Value; }

	void setPos(Vector2 pos) { m_Pos = pos; }
	Vector2 getPos() { return m_Pos; }

	Vector2 getBoardPos() { return m_BoardPos; }

	void setMarker(string marker) { m_Marker = marker; }
	string getMarker() { return m_Marker; }

private:
	int m_Value;
	Vector2 m_BoardPos;

	string m_Marker = "--";

	Vector2 m_Pos;
};

class Cursor {
public:
	Cursor();
	virtual ~Cursor() {}

	ConsoleWindow draw(ConsoleWindow window, Vector2 pos);

	void SetPos(Vector2 a_Pos) { m_Pos = a_Pos; }
	Vector2 getPos() { return m_Pos; }
private:
	Vector2 m_Pos;
	ColourClass Colour;
};

class Player {
public:
	Player(string Marker);
	virtual ~Player() {}

	string getMarker() { return m_Marker; }

	void AddValue(int val) { values.push_back(val); }
	vector<int> GetValues() { return values; }

	void clearVals() { values.clear(); }
private:
	string m_Marker;
	vector<int> values = vector<int>{};
};

class TicTacToe : public SYDEWindowGame {
public:
	TicTacToe();
	virtual ~TicTacToe() {}

	TicTacToePiece atPos(Vector2 pos);
	void MarkerAtPos(Vector2 pos, Player &player);

	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	ConsoleWindow draw_board(ConsoleWindow window);

	bool CheckWinner(Player player);
private:
	SYDELabel __player1winstally = SYDELabel("Player 1 Wins: 0", Vector2(22, 7), Vector2(18, 1), BLACK, true);
	SYDELabel __player2winstally = SYDELabel("Player 2 Wins: 0", Vector2(22, 8), Vector2(18, 1), BLACK, true);
	SYDELabel __drawstally = SYDELabel("Drawn: 0", Vector2(22, 9), Vector2(18, 1), BLACK, true);

	vector<TicTacToePiece> m_Board;
	CustomAsset m_bg;
	Cursor m_Cursor;
	AssetsClass astVars;
	Player Player1 = Player("><");
	Player Player2 = Player("()");

	bool Play1Turn = true;

	int turns = 0;

	bool winner = false;
	bool border = false;

	int player1wins = 0;
	int player2wins = 0;
	int drawn = 0;

};