#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include "Gra.h"

using namespace std;

void zapiszGre(GraS game)
{
	ofstream plik;
		
	plik.open("gra.txt", ios::out);
	
	for (int i = 0; i < 4; i++)
	{
		plik << game.szyfr[i] << endl;
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			plik << game.Tab[i][j] << endl;
		}
	}
	
	plik << game.runda << endl;
	plik << game.tura << endl;

	plik.close();
}

void wczytajGre(GraS& game)
{
	ifstream plik;

	plik.open("gra.txt", ios::in  /*ios::trunc*/);

	if (plik.is_open())
	{
		for (int i = 0; i < 4; i++)
		{
			plik >> game.szyfr[i];
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				plik >> game.Tab[i][j];
			}
		}

		plik >> game.runda;
		plik >> game.tura;
	}
	plik.close();

	ofstream file;

	file.open("gra.txt", ios::trunc);

	file.close();
}


bool sprGra()
{
	ifstream file;
	file.open("gra.txt", ios::in);

	return file.peek() != ifstream::traits_type::eof();
}

int sprDane(char d)
{
	if (d <= '9' && d >= '1')
		return 2;
	else
	{
		if (d == 'w' || d == 'W')
			return 1;
		else
			return 0;
	}
}

void nowaGra(GraS& game)
{
	game.stanGry = 0;
	game.runda = 0;
	game.tura = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			game.Tab[i][j] = 10;
		}
	}
	game.Tab[0][0] = 0;
	losuj(game);
}

void spr(GraS& game)
{
	int p1 = 0, p2 = 0;
	for (int j = 0; j < 4; j++)
	{
		if (game.Tab[game.runda][j] == game.szyfr[j])
			p1++;
	}

	for (int j = 0; j < 4; j++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (game.Tab[game.runda][c] == game.szyfr[j])
				p2++;
		}
	}
	game.Tab[game.runda][4] = p1;
	game.Tab[game.runda][5] = (p2-p1);
}

void xGra(GraS& game, int k)
{	
	if (k == 0)
	{
		nowaGra(game);
	}
	else
	{
		if (sprGra())
		{
			wczytajGre(game);
		}
		else
		{
			cout << "Nie ma gry do kontynuacji" << endl;
			game.stanGry = 0;
			return;
		}
	}

	char d;

	for (int i = game.runda; i < 8; i++, game.runda++)
	{
		for (int j = game.tura; j < 4; j++ , game.tura++)
		{
			ekran(game);
			cin >> d;
			int a = sprDane(d);
			switch(a)
			{
			case 2: 
			{
				game.Tab[i][j] = (d - 48); 
				game.blad = 0;
				break;
			}

			case 1:
			{
				zapiszGre(game);
				game.stanGry = 3;
				return;
				break;
			}

			default:
			{
				j--;
				game.tura--;
				game.blad = 1;
				break;
			}

			}
		}
		spr(game);

		if (game.Tab[game.runda][4] == 4)
		{
			system("cls");
			cout << "Wygrales :)" << endl;
			game.stanGry = 0;
			return;
		}

		game.tura = 0;
	}

	system("cls");
	cout << "Przegrales :(" << endl;
	game.stanGry = 0;
}

void losuj(GraS& game) 
{
	srand(time(NULL));

	for (int i = 0; i < 4; i++)
	{
		game.szyfr[i] = (rand()%9)+1;
	}


}

void ekran(GraS game)
{
	system("cls");
	cout << "Twoim zadanie jest rozszyfrowac jakie 4 cyfry wylosowal komputer." << endl;
	cout << "Punkty A to ilosc odpowiednich liczb na odpowiednich miejscach." << endl;
	cout << "Punkty B to ilosc odpowiednich liczb na nieodpowiednich miejscach." << endl;
	cout << "Jesli chcesz wyjsc z gry wpisz < w >." << endl;
	cout << endl;
	cout << "Cyfra 1 \t Cyfra 2 \t Cyfra 3 \t Cyfra 3 \t Punkty A \t Punkty B" << endl;

	/*for (int i = 0; i < 4; i++)
	{
		cout << game.szyfr[i];
	}*/

	// pomocnicze wypisywanie szyfru na ekran

	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i < game.runda || (i == game.runda && j < game.tura))
			{
				cout << "   " << game.Tab[i][j] << "\t\t";
			}
			else
			{
				if (i == game.runda && j == game.tura)
				{
					cout << "   " << "_" << "\t\t";
				}
				else
				{
					cout << "   " << "x" << "\t\t";
				}
			}
		}
		cout << endl << endl;
	}

	if (game.blad == 1)
		cout << "Bledne dane!" << endl;

	cout << "Wpisz liczbe:";
}


int menu(GraS& game)
{
	if (game.kont == 1)
	{
		cout << "Niestety nie ma zapisanej gry. Mozna zaczac nowa" << endl;
	}

	cout << "1. Nowa gra" << endl;
	cout << "2. Kontynuj" << endl;
	cout << "3. Wyjscie"  << endl;
	cout << "Wybierz: ";
	int w = 0;

	cin >> w;

	switch (w)
	{
	case 1: 
		{	
			system("cls");
			return w;
			break;
		}
	case 2:
		{
			system("cls");
			return w;
			break;
		}
	case 3:
		{
			system("cls");
			return 3;
			break;
		}
	default:
		{
			system("cls");
			cout << "Nie ma takiej opcji" << endl;
			cin.ignore(1);
			return 0;
			break;
		}
	}
	system("cls");
}