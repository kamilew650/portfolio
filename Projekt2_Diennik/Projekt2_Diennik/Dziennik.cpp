#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Dziennik.h"

using namespace std;


void zapiszDziennik(LUczen* glowa, int ilosc)
{
	ofstream file("zapis.txt", ios::binary); //otwieranie pliku binarnego do zapisu
	if (file.is_open())
	{
		file.write((char*)(&ilosc), sizeof(int)); //zapisanie ilosci uczniow

		for (int i = 0; i < ilosc && glowa; i++, glowa = glowa->nastU) //zapisywanie danych ucznia
		{
			string::size_type imie_size = glowa->uczen.imie.size();
			file.write((char*)(&imie_size), sizeof(string::size_type));
			file.write(glowa->uczen.imie.data(), imie_size);

			string::size_type nazwisko_size = glowa->uczen.nazwisko.size();
			file.write((char*)(&nazwisko_size), sizeof(string::size_type));
			file.write(glowa->uczen.nazwisko.data(), nazwisko_size);

			string::size_type data_size = glowa->uczen.data.size();
			file.write((char*)(&data_size), sizeof(string::size_type));
			file.write(glowa->uczen.data.data(), data_size);

			string::size_type miejsce_size = glowa->uczen.miejsce.size();
			file.write((char*)(&miejsce_size), sizeof(string::size_type));
			file.write(glowa->uczen.miejsce.data(), miejsce_size);

			file.write((char*)(&glowa->uczen.iloscOcen), sizeof(int));

			LOcena* e = glowa->uczen.glowaOcen;

			for (int j = 0; j < glowa->uczen.iloscOcen && glowa->uczen.glowaOcen; j++, e = e->nastO) //zapisywanie danych ucznia
			{
				file.write((char*)(&glowa->uczen.glowaOcen->ocena.stopien), sizeof(int));
				
				string::size_type ocena_size = e->ocena.opis.size();
				file.write((char*)(&ocena_size), sizeof(string::size_type));
				file.write(e->ocena.opis.data(), ocena_size);
			}

		}
	}
	file.close();
}

void wczytajDziennik(LUczen*& glowa, int& ilosc)
{
	usunDziennik(glowa);		//usuwanie ewentulanych danych

	ifstream file("zapis.txt", ios::binary); //otwarcie pliku binarnego do odczytu

	if (file.good())
	{
		string::size_type imie_size;
		string::size_type nazwisko_size;
		string::size_type data_size;
		string::size_type miejsce_size;
		string::size_type opis_size;
		

		Uczen u;
		Ocena o;
		LUczen* g = glowa;

		
		int znacznik = 0; // przechowuje ilosc uczniow
		
		if (!file.eof()) //wczytanie ilosci uczniow
		{
			file.read((char*)(&znacznik), sizeof(int));
			ilosc = znacznik;
		}

		for (int i = 0; i < znacznik && !file.eof(); i++) //wczytanie danych ucznia
		{

			file.read((char*)(&imie_size), sizeof(string::size_type));
			u.imie.resize(imie_size);
			file.read(&u.imie[0], imie_size);

			file.read((char*)(&nazwisko_size), sizeof(string::size_type));
			u.nazwisko.resize(imie_size);
			file.read(&u.nazwisko[0], imie_size);

			file.read((char*)(&data_size), sizeof(string::size_type));
			u.data.resize(imie_size);
			file.read(&u.data[0], imie_size);

			file.read((char*)(&miejsce_size), sizeof(string::size_type));
			u.miejsce.resize(imie_size);
			file.read(&u.miejsce[0], imie_size);

			file.read((char*)(&u.iloscOcen), sizeof(int));

			dodajUcznia(glowa, u); //dodanie ucznia
			
			if (i == 0)
				g = glowa;
			else
				g = g->nastU;

			for (int j = 0; j < u.iloscOcen && !file.eof(); j++) //wczytanie informacji o ocenie 
			{
				file.read((char*)(&o.stopien), sizeof(int));

				file.read((char*)(&opis_size), sizeof(string::size_type));
				o.opis.resize(imie_size);
				file.read(&o.opis[0], imie_size);

				dodajOcene(g, o); //dodanie oceny
			}
		}


	}
}

void dziennikWybierzUcznia(LUczen*& glowa)
{
	int numerUcznia, stanMenu = 0;
	LUczen* u;
	
	wyswietlDziennik(glowa, 0); // wypisuje wszystkiech uczniow alby mo¿na by³o wybraæ odpowiedniego

	cout << endl << "Podaj aktualny numer ucznia: " << endl;
	cin >> numerUcznia;

	u = wybierzUcznia(glowa, numerUcznia); //znajduje i zwraca wska¿nik na odpowiedniego ucznia


	do
	{
		switch (stanMenu)
		{
		case 0:
		{	
			system("cls");
			cout << u->uczen.imie << " ";     //wypisuje dane wybranego ucznia
			cout << u->uczen.nazwisko << " ";
			cout << u->uczen.data << " ";
			cout << u->uczen.miejsce << endl;

			LOcena* e = u->uczen.glowaOcen;

			while (u->uczen.glowaOcen != nullptr)
			{
				cout << "\t< " << u->uczen.glowaOcen->ocena.stopien << " | " << u->uczen.glowaOcen->ocena.opis << " >" << endl;
				u->uczen.glowaOcen = u->uczen.glowaOcen->nastO;
			}

			u->uczen.glowaOcen = e;

			stanMenu = menuWyboru(); //zmienna okreœla operacje jakie bêd¹ wykonane
			break;
		}
		case 1:
		{
			system("cls");
			dziennikDodajOcene(u); //dodaje ocene
			u->uczen.iloscOcen++;
			system("cls");
			stanMenu = 0;
			break;
		}
		case 2:
		{	
			dziennikEdytujUcznia(u); //pozwala edytowaæ dane ucznia
			system("cls");
			stanMenu = 0;
			break;
		}
		case 3:
		{
			system("cls");
			usunUcznia(glowa, u); //usuwa wybranego wczeœniej ucznia
			stanMenu = 0;
			break;
		}
		}


	} while (stanMenu != 4);
}

void usunUcznia(LUczen*& glowa, LUczen* u)
{
	if (glowa->nastU) //sprawdza czy w liœcie jest tylko jeden element
	{
		if (glowa != u) //sprawdza czy glowa jest wybranym elementem
		{
			while (glowa != nullptr && glowa->nastU != u)
			{
				glowa = glowa->nastU;
			}												//
			glowa->nastU = u->nastU;						//usuwa element 
			delete u;										//
		}
		else
		{

			glowa = u->nastU;
			delete u;
		}
	}
	else
	{
		cout << "Nie mozna usunac jedynego ucznia" << endl;
		int i;
		cin >> i;
		system("cls");
	}
}

LUczen* wybierzUcznia(LUczen* glowa, int nr)
{
	int i = 1;
	while (glowa != nullptr && i < nr) //znajduje ucznia i zwraca wska¿nik na niego
	{
		glowa = glowa->nastU;
		i++;
	}
	return glowa;
}

void usunDziennik(LUczen*& glowa)
{
	LUczen* e = glowa;  //wskaznik pomocniczy dla listy uczniow
	LOcena* o;			//wskaznik pomocniczy dla listy ocen
	while (glowa != nullptr)
	{
		o = glowa->uczen.glowaOcen;
		while (glowa->uczen.glowaOcen != nullptr) //usuwa wszystkie oceny danego ucznia
		{
			glowa->uczen.glowaOcen = glowa->uczen.glowaOcen->nastO;
			delete o;
			o = glowa->uczen.glowaOcen;
		}
		glowa = glowa->nastU; 
		delete e; //usuwa ucznia  
		e = glowa;
	}
}

void wyswietlDziennik(LUczen* glowa, int a)
{
	int i = 1;
	while (glowa != nullptr)
	{
		cout << i << ". ";						//wypisuje dane uczniow
		cout << glowa->uczen.nazwisko << " ";
		cout << glowa->uczen.imie << " ";
		cout << glowa->uczen.data << " ";
		cout << glowa->uczen.miejsce << endl;

		while (glowa->uczen.glowaOcen != nullptr)		// wypisuje oceny uczniow
		{
			cout << "\t< " << glowa->uczen.glowaOcen->ocena.stopien << " | " << glowa->uczen.glowaOcen->ocena.opis << " >" << endl;
			glowa->uczen.glowaOcen = glowa->uczen.glowaOcen->nastO;
		}

		glowa = glowa->nastU;
		i++;
	}
	if (a)		//w zaleznosi od a czeka na wczytanie liczby lub nie
	{
		cin >> i;
	}
}

void edytujUcznia(LUczen* u, Uczen ucz)
{
	ucz.glowaOcen = u->uczen.glowaOcen;
	ucz.iloscOcen = u->uczen.iloscOcen; //podmienia stare dane ucznia na nowe
	u->uczen = ucz;
	
}

void dodajOcene(LUczen*& uczen, Ocena ocena)
{
	LOcena* e = uczen->uczen.glowaOcen;
	LOcena* o = new LOcena();
	o->ocena = ocena;
	o->nastO = nullptr;
	if (uczen->uczen.glowaOcen == nullptr)	 //sprawdza czy lista ocen jest pusta
	{
		uczen->uczen.glowaOcen = o;
	}
	else
	{
		while (uczen->uczen.glowaOcen->nastO != nullptr) //idzie na koniec listy ocen
		{
			uczen->uczen.glowaOcen = uczen->uczen.glowaOcen->nastO;
		}
		uczen->uczen.glowaOcen->nastO = o;
		uczen->uczen.glowaOcen = e;
	}
}

void dodajUcznia(LUczen*& glowa, const Uczen uczen)
{	
	LUczen* g = glowa;
	LUczen* e = new LUczen();
	e->uczen = uczen;
	e->uczen.glowaOcen = nullptr;
	if (glowa != nullptr)
	{
		if (glowa->nastU != nullptr)
		{
			while (glowa->nastU->nastU != nullptr && (uczen.nazwisko > glowa->nastU->uczen.nazwisko || (      // dodawanie w kolejnosci alfabetycznej
				uczen.nazwisko == glowa->nastU->uczen.nazwisko && uczen.imie > glowa->nastU->uczen.imie))
				&& (uczen.nazwisko > glowa->uczen.nazwisko ||uczen.nazwisko == glowa->uczen.nazwisko &&
					uczen.imie > glowa->uczen.imie))
			{
				glowa = glowa->nastU;
			}

			if (glowa == g && (uczen.nazwisko < glowa->uczen.nazwisko ||
				uczen.nazwisko == glowa->uczen.nazwisko && uczen.imie < glowa->uczen.imie))
			{
				e->nastU = glowa;
				glowa = e;
			}
			else
			{
				if (uczen.nazwisko < glowa->nastU->uczen.nazwisko ||
					uczen.nazwisko == glowa->nastU->uczen.nazwisko && uczen.imie < glowa->nastU->uczen.imie)
				{
					e->nastU = glowa->nastU;
					glowa->nastU = e;
				}
				else
				{
					glowa->nastU->nastU = e;
				}
				glowa = g;
			}
		}
		else
		{
			if (uczen.nazwisko < glowa->uczen.nazwisko ||
				uczen.nazwisko == glowa->uczen.nazwisko && uczen.imie < glowa->uczen.imie)
			{
				e->nastU = glowa;
				glowa = e;
			}
			else
			{
				if (glowa->nastU && (uczen.nazwisko < glowa->nastU->uczen.nazwisko ||
					uczen.nazwisko == glowa->nastU->uczen.nazwisko && uczen.imie < glowa->nastU->uczen.imie))
				{
					e->nastU = glowa->nastU;
					glowa->nastU = e;
				}
				else
				{
					glowa->nastU = e;
				}
			}
		}

	}
	else
	{
		glowa = e;
	}
	
}

void dziennikEdytujUcznia(LUczen* u)
{
	Uczen ucz;
	cout << "Wprowadz nowe dane ucznia:" << endl; //wczytuje nowe dane ucznia

	cout << "Imie:" << endl;
	cin >> ucz.imie;

	cout << "Nazwisko:" << endl;
	cin >> ucz.nazwisko;

	cout << "Data urodzenia:" << endl;
	cin >> ucz.data;

	getline(cin, ucz.data);	// wyczyszczenie strumienia wyjscia ze znaku konca linii

	cout << "Miejsce urodzenia:" << endl;
	getline(cin, ucz.miejsce);
	
	edytujUcznia(u, ucz);
}

void dziennikDodajOcene(LUczen*& u)
{
	Ocena o;
	cout << "Podaj ocene: "; //wczytuje dane o ocenie
	cin >> o.stopien;
	cout << "Podaj opis oceny: ";

	getline(cin, o.opis); // wyczyszczenie strumienia wyjscia ze znaku konca linii

	getline(cin, o.opis);
	dodajOcene(u, o);
}

void dziennikDodajUcznia(LUczen*& glowa)
{
	Uczen u;
	cout << "Wprowadz dane ucznia:" << endl; //wczytuje dane ucznia

	cout << "Imie:" << endl;
	cin >> u.imie;

	cout << "Nazwisko:" << endl;
	cin >> u.nazwisko;

	cout << "Data urodzenia:" << endl;
	cin >> u.data;

	getline(cin, u.miejsce);	// wyczyszczenie strumienia wyjscia ze znaku konca linii

	cout << "Miejsce urodzenia:" << endl;
	getline(cin, u.miejsce);

	dodajUcznia(glowa, u);
}


int menuWyboru()
{

	cout << "1. Dodaj ocene" << endl; //wyœwietla opcje na ekran
	cout << "2. Edytuj ucznia" << endl;
	cout << "3. Usun ucznia" << endl;
	cout << "4. Powrot" << endl;
	cout << "Wybierz: ";
	int w = 0;

	cin >> w; //wczytuje z klawiatury liczbe okreœlaj¹c¹ dalsze dzia³anie programu

	if (w < 5 && w > 0) //sprawdza poprawnoœæ danych
	{
		return w;
	}
	else
	{
		system("cls");
		cout << "Nie ma takiej opcji" << endl;
		return 0;
	}
}


int menuGlowne()
{
	system("cls");

	cout << "1. Wyswietl baze danych" << endl; //wyœwietla mo¿liwe opcje na ekran
	cout << "2. Dodaj ucznia" << endl;
	cout << "3. Wybierz ucznia" << endl;
	cout << "4. Wczytaj dane z pliku" << endl;
	cout << "5. Zapisz dane w pliku" << endl;
	cout << "6. Wyjscie" << endl;
	cout << "Wybierz: ";
	int w = 0;

	cin >> w; //wczytuje liczbe okreœlaj¹c¹ dalsze dzia³anie programu

	if (w < 7 && w > 0) //sprawdza poprawnoœæ
	{
		return w;
	}
	else
	{
		system("cls");
		cout << "Nie ma takiej opcji" << endl;
		return 0;
	}
	cin.clear();
}