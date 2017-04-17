#include <iostream>
#include "Gra.h"

using namespace std;

int main()
{
	GraS game = { 0 };

	do
	{
		switch (game.stanGry)
		{
		case 0:
		{
			game.stanGry = menu(game);
			break;
		}
		case 1:
		{
			xGra(game, 0);
			break;
		}
		case 2:
		{
			xGra(game, 1);
			break;
		}
		}


	} while (game.stanGry != 3);

	return 0;
}