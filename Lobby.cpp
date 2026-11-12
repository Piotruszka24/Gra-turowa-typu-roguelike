#include <iostream>
#include <vector>
#include <time.h>
#include <conio.h>

#define en '\n'
	
const int WYSOKOSC_ = 8;
const int SZEROKOSC_ = 22;
const int ZDROWIE_ = 20;
	
char plansza[WYSOKOSC_][SZEROKOSC_]; //PLANSZA[Y][X]

class Player{
	public:
		Player(int x1, int y1){
			x = x1;
			y = y1;
			hp = ZDROWIE_;
		}
		
		void narysuj_polozenie_gracza(){
			plansza[this->y][this->x] = '@';
		}
		
		void zmiana_pozycji_gracza(int x_nowe, int y_nowe){
			this->x = x_nowe;
			this->y = y_nowe;
		}
		
		void usuwanie_starej_pozycji_gracza(int x_stare, int y_stare){
			plansza[y_stare][x_stare] = '.';
		}
		
		bool czy_moze_sie_przemiescic(int x_nowe, int y_nowe){
			bool czy_moze = true;
			//sprawdzanie czy za granica mapy
			if(x_nowe > SZEROKOSC_ - 2) czy_moze = false;
			if(x_nowe < 1) czy_moze = false;
			if(y_nowe > WYSOKOSC_ - 2) czy_moze = false;
			if(y_nowe < 1) czy_moze = false;
			//sprawdzanie czy nie pzrechodzi przez sciany miedzy pokojami
			if(plansza[y_nowe][x_nowe] == char(219)) czy_moze = false;
			return czy_moze;
		}
		
		int wez_szerokosc(){
			return x;
		}
		
		int wez_wysokosc(){
			return y;
		}
		
	private:
		int x;
		int y;
		int hp;
};

int main(){
		
	srand(time(0));
		
	//Rysowanie pustej planszy zapełnionej scianami
		
	for(int i=0; i<WYSOKOSC_; i++){
		for(int j=0; j<SZEROKOSC_; j++) plansza[i][j]= char(219);
	}
		
	//drazenie dziury w lobby
	
	for(int i=1; i<WYSOKOSC_-1; i++){
		for(int j=1; j<SZEROKOSC_-1; j++) plansza[i][j]= '.';
	}
	
	
	//polozenie gracza
	
	int x_gr = rand() % 20 + 1;
	int y_gr = rand() % 6 + 1;
	
	Player gracz(x_gr, y_gr);
	gracz.narysuj_polozenie_gracza();
	
	//rysowanie planszy
	
	for(int i=0; i<WYSOKOSC_; i++){
		for(int j=0; j<SZEROKOSC_; j++) std::cout << plansza[i][j];
		std::cout << en;
	}
	
	//chodzenie po planszy
	
	bool gra_trwa = true;
	
	while(gra_trwa){
		char klawisz = _getch(); 
		system("cls");

		int x_nowe = gracz.wez_szerokosc();
		int y_nowe = gracz.wez_wysokosc();
		int x_stare = x_nowe;
		int y_stare = y_nowe;

        switch (klawisz) {
			
			case 'w': y_nowe--; break; // Góra
            case 's': y_nowe++; break; // Dół
            case 'a': x_nowe--; break; // Lewo
            case 'd': x_nowe++; break; // Prawo
            case 'q': gra_trwa = false; break;
        }
        
        if(gracz.czy_moze_sie_przemiescic(x_nowe, y_nowe)) { //tu cos nie dziala
			gracz.zmiana_pozycji_gracza(x_nowe, y_nowe);
        	gracz.usuwanie_starej_pozycji_gracza(x_stare, y_stare);
        	gracz.narysuj_polozenie_gracza();
    	}
        
        for(int i=0; i<WYSOKOSC_; i++){
			for(int j=0; j<SZEROKOSC_; j++) 
				std::cout << plansza[i][j];
			std::cout << en;
		}
        
	}
	
}
