#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <windows.h>
#ifndef SAPER_
#define SAPER
#define size 20
#define multi 1


class Bomb;

class Map
{
	private:
		int Moves;
		int BombNum;
		int flags;
		char Bar_[size][5];
		char Map_[size][size];
		char Map_B[size][size];
		int x;
		int y;
		int Score;
		int HideScore;
		
	public:
		Map();
		void InitBar();
		void InitMap();
		void Move(char key);
		void Recolour();
		void DrawBar();
		void DrawMap();
		void ShowXY();
		void AddHideScore();
		void SubHideScore();
		void OpenFree(int *exit);
		void PlaceBomb();
		void AddBombs(Bomb b[size*multi]);
		//gotoxy function
		void gotoxy(int x, int y);
		void AddBomb(){BombNum++;
		}
		int CheckBombs(){
			return BombNum;
		}
		//clear of console with buffer
		void cls();
		bool IsFree(int x, int y);
		void DrawNumbers(int x, int y);
		void OpenBox(int x, int y);
		int GiveMoves();
		bool IsTile();
		void FlagTile();
		void WinCondition(int *exit);
		int ScoreSum();
};

class Bomb
{
	int id;
	int x;
	int y;
	
	public:
		int GiveX();
		int GiveY();
		void Boom();
		void Generate(Bomb b[size*multi], int i);
		bool CheckPos(Bomb b[size*multi]);
};




#endif
