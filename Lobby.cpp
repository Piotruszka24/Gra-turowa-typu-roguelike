#include <iostream>
#include <vector>
#include <time.h>
	
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
}
