#include <iostream>

#include "saper_.h"


using namespace std;

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	Map map;
	static int exit=1;
	char key;
	map.Map::InitMap();
	map.Map::InitBar();
	Bomb bomb[size*multi];
	for(int i=0;i<size*multi;i++)bomb[i].Bomb::Generate(bomb, i);
	map.AddBombs(bomb);
	for(int i = 0;i<size*multi;i++)
	{
		map.DrawNumbers(bomb[i].Bomb::GiveX(), bomb[i].Bomb::GiveY());
	}
	
	while(exit)
	{
	
	map.Map::DrawBar();
	map.Map::DrawMap();
	
		key=getch();
	
	map.Map::Move(key);
	if(key=='e' || key=='\n' || key==32)
		{
		if(map.Map::GiveMoves()==0)
		{
			while(map.IsTile()==false)
			{
				map.Map::Move('w');
				map.Map::Move('a');
			}
		}
	map.Map::OpenFree(&exit);
	}
	
	if(key=='f')
	map.FlagTile();
	map.WinCondition(&exit);
	
	continue;
	}
	
}

