#include <string>


using namespace std;



struct Ocena  //zawiera informacje o ocenie
{
	int		stopien; 
	string	opis;
};

struct LOcena //element listy ocen
{
	Ocena	ocena;
	LOcena* nastO = nullptr; //wska�nik do nastepnego elementu
};

struct Uczen //zawiera inforamcje o uczniu
{
	string	imie;
	string	nazwisko;
	string	data;
	string	miejsce;
	int		iloscOcen = 0; //zmienna zawiera informacje pomocne przy operowaniu na li�cie ocen danego ucznia
	LOcena* glowaOcen = nullptr; //wskazuje wierwszy element listy ocen
};


struct LUczen //element listy uczni�w
{ 
	Uczen	uczen;   
	LUczen*	nastU; //wska�nik do nastepnego elementu
};

struct Dziennik //struktura przechowujaca wszystkie dane potrzebne do poprawnego funkcjonowania programu
{
	LUczen* glowa = nullptr;
	int iloscUczniow = 0; //zmienna przechowujaca informacje o ilo�ci uczni�w
	int stan = 0;
};