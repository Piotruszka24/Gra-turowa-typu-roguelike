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
		
		void przyjmij_obrazenia(int ile){
			hp -=ile;
		}
		
	private:
		int x;
		int y;
		int hp;
};

class Przeciwnik{
	protected:
		int x;
		int y;
		int hp;
	public:
		Przeciwnik(int x_p, int y_p, int zycie) : x(x_p), y(y_p), hp(zycie) {;}
		virtual void zaatakuj(Player& gracz) = 0;
		virtual bool wykonaj_ruch_przeciwnik(int x_gracz, int y_gracza) = 0;
		virtual void pojaw_sie_na_mapie(int x_prz, int y_prz) = 0;
		virtual void zmien_pozycje(int x_nowe, int y_nowe, int x_stare, int y_stare) = 0;
		std::string dostan_obrazenia(int ilosc){
			hp -= ilosc;
			if(hp <= 0) return "Przeciwnik zabity\n";
			else return "Przeciwnik trafiony\n";
		}
		
		bool czy_moze_zaatakowac(){
			for(int i = this->x -1; i <= this->x +1; i++){
				for(int j = this->y - 1; j <= this-> y + 1; j++){
					if(plansza[j][i] == '@') return true;
				}
			}
			return false;
		}

};

class Zombie : public Przeciwnik {
	private:
		int ilosc_zadawanych_obrazen{5};
	public:
		Zombie(int x_p, int y_p, int zycie) : Przeciwnik(x_p, y_p, zycie){;}
		void zaatakuj(Player& gracz) override{
			if(this->czy_moze_zaatakowac()) gracz.przyjmij_obrazenia(ilosc_zadawanych_obrazen);
		}
		
		bool wykonaj_ruch_przeciwnik(int x_gracza, int y_gracza) override{
			if(x_gracza > this->x && plansza[this->y][this->x + 1] == '.'){
				zmien_pozycje(this->x + 1, this->y, this->x, this->y);
				return true;
			}
			else if(x_gracza < this->x && plansza[this->y][this->x - 1] == '.'){
				zmien_pozycje(this->x - 1, this->y, this->x, this->y);
				return true;
			}
			else if(y_gracza > this->y && plansza[this->y + 1][this->x] == '.'){
				zmien_pozycje(this->x, this->y + 1, this->x, this->y);
				return true;
			}
			else if(y_gracza < this->y && plansza[this->y - 1][this->x] == '.'){
				zmien_pozycje(this->x, this->y - 1, this->x, this->y);
				return true;
			}
			return false;
		}
		
		void zmien_pozycje(int x_nowe, int y_nowe, int x_stare, int y_stare) override{
			plansza[y_stare][x_stare] = '.';
			plansza[y_nowe][x_nowe] = 'Z';
		}
		
		void pojaw_sie_na_mapie(int x_prz, int y_prz) override{
			plansza[y_prz][x_prz] = 'Z';		
		}
};

void tura_gracza(Player& gracz, bool& gra_trwa){
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
        
    if(gracz.czy_moze_sie_przemiescic(x_nowe, y_nowe)) { 
		gracz.zmiana_pozycji_gracza(x_nowe, y_nowe);
       	gracz.usuwanie_starej_pozycji_gracza(x_stare, y_stare);
       	gracz.narysuj_polozenie_gracza();
    }
}

void tura_przeciwnikow(){
	;
}

void rysowanie_planszy(){
	for(int i=0; i<WYSOKOSC_; i++){
		for(int j=0; j<SZEROKOSC_; j++) 
			std::cout << plansza[i][j];
		std::cout << en;
	}
}

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
	
	
	//polozenie gracza i pojawiwenie sie go na mapie
	
	int x_gr = rand() % 20 + 1;
	int y_gr = rand() % 6 + 1;
	
	Player gracz(x_gr, y_gr);
	gracz.narysuj_polozenie_gracza();
	
	//pojawienie sie potwora na mapie
	
	for(int i=0; i < 100; i++){
		int x_prz = rand() % 20 + 1;
		int y_prz = rand() % 6 + 1;
			
		if(plansza[y_prz][x_prz] == '.'){
			Zombie p1(x_prz, y_prz, 20);
			p1.pojaw_sie_na_mapie(x_prz, y_prz);
			break;
		}
	}
	
	
	//rysowanie planszy
	
	for(int i=0; i<WYSOKOSC_; i++){
		for(int j=0; j<SZEROKOSC_; j++) std::cout << plansza[i][j];
		std::cout << en;
	}
	
	//chodzenie po planszy
	
	bool gra_trwa = true;
	
	while(gra_trwa){
		tura_gracza(gracz, gra_trwa);
        rysowanie_planszy();
	}
	
}
