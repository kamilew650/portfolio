#pragma once
#include "Uczen_Ocena.cpp"

void dziennikDodajUcznia(LUczen*& glowa); //funkcja nadzorujaca dodawanie ucznia

	void dodajUcznia(LUczen*& glowa, const Uczen uczen); //dodaje ucznia uwzgledniajac kolejnosc alfabetyczna

void dziennikWybierzUcznia(LUczen*& glowa);  // nadzoruje funkcje operujace na danym uczniu

	LUczen* wybierzUcznia(LUczen* glowa, int nr); //wyszukuje ucznia po indeksie

	void dziennikEdytujUcznia(LUczen* uczen); //nadzoruje edytowanie danych ucznia

		void edytujUcznia(LUczen* u, Uczen ucz); //zmienia dane i umozliwia usuwanie i edycje ocen

	void dziennikDodajOcene(LUczen*& uczen); // nadzoruje dodawanie ocen

		void dodajOcene(LUczen*& uczen, Ocena ocena); // dodaje ocene podanemu uczniowi

		void usunUcznia(LUczen*& glowa, LUczen* u);  //usuwanie wy³acznie po indeksie by nie bylo pomy³ki

void wyswietlDziennik(LUczen* glowa, int a); // wyswietla cala baze danych

void zapiszDziennik(LUczen* glowa, int ilosc); // zapisuje dziennik

void wczytajDziennik(LUczen*& glowa, int& ilosc); // wczytuje dziennik

int menuGlowne(); // pelni funkcje menu

int menuWyboru(); //pelni funkcjie menu wyboru

void usunDziennik(LUczen*& glowa); // usuwa wszystkie dane