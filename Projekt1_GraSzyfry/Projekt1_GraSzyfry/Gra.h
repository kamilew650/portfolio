#pragma once
#include "GraS.cpp"


		void spr(GraS& game); // metoda sprawdzajaca poprawnosc podanego przez uzytkownika kodu

		void xGra(GraS& game, int k);  // w zaleznosci od argumentu wczytuje gra badz rozpoczyna na nowo
			
			bool sprGra(); //sprawdza czy w pliku jest zapis gry

			int sprDane(char d); // sprawdza poprawnosc danych wprowadzonych przez uzytkownika 

			void wczytajGre(GraS& game); // wczytuje gre z pliku

			void zapiszGre(GraS game); // zapisuje gre do pliku

			void nowaGra(GraS& game);  // tworzy nowa gre

			void losuj(GraS& game); //losuje szyfr

		void ekran(GraS game);  // metoda wyswietla ekran rozgrywki

		int menu(GraS& game);  // metoda wyswietlajaca menu i okreœlajaca stan gry w zale¿noœci od pobranych danych


