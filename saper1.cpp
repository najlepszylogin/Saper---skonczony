#include "saper_.h"

#define block 219
#define tile 177
#define bomb 42
#define flag 94
#define tileopen 176


using namespace std;

void Map::DrawBar()
{
	
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(i==0 || i==4 || j==0 || j==size-1)
			{
				cout << Bar_[j][i];
				
			}else
			{
				cout << Bar_[j][i];
			}
			
			
		}
		cout << endl;
	}
	gotoxy(2,2);
	cout << "BOMB: " << BombNum;
	gotoxy(12,2);
	cout << Score;
}

int Map::GiveMoves()
{
	return Moves;
}

void Map::DrawMap()
{

	ShowXY();
	gotoxy(0,4);
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(i==0 || i==size-1 || j==0 || j==size-1)
			{
				cout << Map_[j][i];
				
			}else
			{
				if(i==y && j==x)
				{
					Recolour();
				}else{
				if(Map_[j][i]==char(flag))
				{
					HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute( hOut, 14 );
					cout << Map_[j][i];
					SetConsoleTextAttribute( hOut, 15 );
				}
				else{
				
				if(Map_B[j][i]>'0' && Map_[j][i]==char(tileopen))cout << Map_B[j][i];
				else
				cout << Map_[j][i];
					}
				}
			}
			
		}
		cout << endl;
	}
}

void Map::InitBar()
{
		for(int i=0;i<5;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(i==0 || i==4 || j==0 || j==size-1)
			{
				Bar_[j][i]=block;
				
			}else
			{
				Bar_[j][i]=tile;
			}
			
		}
	}
}

void Map::InitMap()
{
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			if(i==0 || i==size-1 || j==0 || j==size-1)
			{
				Map_[j][i]=block;
				
			}else
			{
				Map_[j][i]=tile;
				Map_B[j][i]='0';
			}
			
		}
	}
}

void Map::gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

void Map::cls()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}
Map::Map()
{
	BombNum = size*multi;
	flags = 0;
	x = size/2;
	y = size/2 + 5;
	Score = 0;
	Moves = 0;
}

void Map::Recolour()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hOut, 2 );
	cout << Map_[x][y];
	SetConsoleTextAttribute( hOut, 15 );
}

void Map::ShowXY()
{
	gotoxy(size+5,5);
	cout <<"X="<< x << "  ";
	gotoxy(size+5,6);
	cout <<"Y="<< y << "  ";
	gotoxy(size+5,7);
	cout << "Moves: " << Moves;
}

void Map::FlagTile()
{
	if(Map_[x][y]==char(tile))
	{
		Map_[x][y]=char(flag);
		BombNum--;
		if(Map_B[x][y]==char(bomb))AddHideScore();
		return;
	}
	if(Map_[x][y]==char(flag))
	{
		Map_[x][y]=char(tile);
		BombNum++;
		if(Map_B[x][y]==char(bomb))SubHideScore();
		return;
	}
}

void Map::Move(char key)
{
	if(key == 'w' && y-1!=0)y--;
	if(key == 's' && y+1!=size-1)y++;
	if(key == 'a' && x-1!=0)x--;
	if(key == 'd' && x+1!=size-1)x++;
	cls();
}

void Map::AddHideScore()
{
	HideScore++;
}

void Map::SubHideScore()
{
	HideScore--;
}

void Map::OpenFree(int *exit)
{
	if(Map_B[x][y]!=char(bomb))
	Map_[x][y] = tileopen;
	else
	{
	gotoxy(1,size+10);
	cout << "Koniec Gry!";
	gotoxy(x,y+4);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hOut, 12);
	cout << char(bomb);
	gotoxy(size,size*2);
	*exit = 0;
	return;
	}
		OpenBox(x,y);
	
	Moves++;
}

void Map::OpenBox(int x, int y)
{
	if(Map_B[x][y]=='0'){
	
	for(int i=x-1;i<=x+1;i++)
	{
		for(int j=y-1;j<=y+1;j++)
		{
			if(Map_[i][j]!=char(block))
			{
				if(Map_[i][j]!=char(tileopen)){
					Map_[i][j]=char(tileopen);
					
						OpenBox(i,j);
			}
			}
		}
	}
	}else 
	Map_[x][y]=char(tileopen);
	

}

bool Map::IsFree(int x, int y)
{
	if(Map_B[x][y]==char(bomb))return false;
	else
	return true;
}

bool Map::IsTile()
{
	if(Map_B[x][y]!='0')return false;
	else
	return true;
}

void Map::AddBombs(Bomb b[size*multi])
{
	for(int i=0;i<size*multi;i++)
	{
		int x = b[i].Bomb::GiveX();
		int y = b[i].Bomb::GiveY();
		Map_B[x][y]=char(bomb);
		
	}
}

void Map::PlaceBomb()
{
	Map_[x][y]=char(bomb);
}

bool Bomb::CheckPos(Bomb b[size*multi])
{
	for(int i = 0 ;i<size*multi;i++)
	{
		if(b[i].x==x && b[i].y==y && i!=id){

		return true;
		
		}
	}
	return false;
	
}

void Bomb::Generate(Bomb b[size*multi], int i)
{
	srand( time( NULL ) );
	id=i;
	do{
		x=(rand()%(size-2))+1;
		y=(rand()%(size-2))+1;
	}while(CheckPos(b)==true);
}

int Bomb::GiveX()
{
	return x;
}
int Bomb::GiveY()
{
	return y;
}

void Map::DrawNumbers(int x, int y)
{
	for(int i=y-1;i<=y+1;i++)
	{
		for(int j=x-1;j<=x+1;j++)
		{
			if(IsFree(j,i)==true)Map_B[j][i]++;
		}
	}
}

void Map::WinCondition(int *exit)
{
	if(HideScore==size*multi)
	{
	gotoxy(1,size+10);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hOut, 11);
	cout << "Koniec Gry! Wygrales z: " << ScoreSum() << " punktami!";
	*exit=0;
	getch();
	}
}

int Map::ScoreSum()
{
	return (size*multi)/Moves;
}



