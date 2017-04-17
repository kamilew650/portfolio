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
	LOcena* nastO = nullptr; //wskaŸnik do nastepnego elementu
};

struct Uczen //zawiera inforamcje o uczniu
{
	string	imie;
	string	nazwisko;
	string	data;
	string	miejsce;
	int		iloscOcen = 0; //zmienna zawiera informacje pomocne przy operowaniu na liœcie ocen danego ucznia
	LOcena* glowaOcen = nullptr; //wskazuje wierwszy element listy ocen
};


struct LUczen //element listy uczniów
{ 
	Uczen	uczen;   
	LUczen*	nastU; //wskaŸnik do nastepnego elementu
};

struct Dziennik //struktura przechowujaca wszystkie dane potrzebne do poprawnego funkcjonowania programu
{
	LUczen* glowa = nullptr;
	int iloscUczniow = 0; //zmienna przechowujaca informacje o iloœci uczniów
	int stan = 0;
};