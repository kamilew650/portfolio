#include <iostream>
#include <cstdlib>
#include "Dziennik.h"

using namespace std;

int main()
{
	Dziennik dziennik = Dziennik();
	do
	{
		switch (dziennik.stan)
		{
		case 0:
		{
			system("cls");
			dziennik.stan = menuGlowne();
			break;
		}
		case 1:
		{	
			system("cls");
			wyswietlDziennik(dziennik.glowa, 1);
			dziennik.stan = 0;
			break;
		}
		case 2:
		{
			system("cls");
			dziennikDodajUcznia(dziennik.glowa);
			dziennik.iloscUczniow++;
			dziennik.stan = 0;
			break;
		}
		case 3:
		{
			system("cls");
			dziennikWybierzUcznia(dziennik.glowa);	
			dziennik.stan = 0;
			break;
		}
		case 4:
		{
			wczytajDziennik(dziennik.glowa, dziennik.iloscUczniow);
			dziennik.stan = 0;
			break;
		}
		case 5:
		{
			zapiszDziennik(dziennik.glowa, dziennik.iloscUczniow);
			dziennik.stan = 0;
			break;
		}
		}


	} while (dziennik.stan != 6);

	usunDziennik(dziennik.glowa);

	return 0;
}