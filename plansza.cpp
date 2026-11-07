#include <iostream>
#include <vector>
#include <time.h>

#define en '\n'

const int WYSOKOSC_ = 20;
const int SZEROKOSC_ = 50;

char plansza[WYSOKOSC_][SZEROKOSC_];

class Pokoj{
	public:
		Pokoj(int x1, int y1, int szer1, int wys1){
			x = x1;
			y = y1;
			szerokosc = szer1;
			wysokosc = wys1;
			srodek_x = (x + x + szerokosc) / 2;
			srodek_y = (y + y + wysokosc) / 2;
		}
		
		bool czy_sie_styka(const Pokoj& drugi){
			bool czy_styka = true;
			if(this->x + this->szerokosc + 1 < drugi.x ||
			   this-> x > drugi.x + drugi.szerokosc + 1 ||
			   this->y + this->wysokosc + 1 < drugi.y  ||
			   this->y > drugi.y + drugi.wysokosc + 1) czy_styka = false;
			return czy_styka;
		}
		
		void rysowanie_pokoju(){
			for(int i=this->x; i < this->x + this->wysokosc; i++){
				for(int j = this->y; j < this->y + this->szerokosc; j++){
					plansza[i][j] = '.';
				}
			}
		}
		
		bool czy_za_mapa(){
			if(this->x + this->szerokosc < SZEROKOSC_ && this->y+ this->wysokosc < WYSOKOSC_) return true;
			return false;
		}
		
	
	private:
		int x;
		int y;
		int szerokosc;
		int wysokosc;
		int srodek_x;
		int srodek_y;
};


int main(){
	
	srand(time(0));
	
	//Rysowanie pustej planszy zapełnionej scianami
	
	for(int i=0; i<WYSOKOSC_; i++){
		for(int j=0; j<SZEROKOSC_; j++) plansza[i][j]= char(219);//char(178);'-';
	}
	
	for(int i=0; i<WYSOKOSC_; i++){
		for(int j=0; j<SZEROKOSC_; j++) std::cout << plansza[i][j];
		std::cout << en;
	}
	
	//tworzenie pokoi - losowej ilosci
	
	std::vector<Pokoj> lista_pokoi;
	int liczba_pokoi = rand() % 4 + 4;
	
	
	for(int i=0; i < liczba_pokoi; i++){
		int ilosc_prob = 0;
		for(; ilosc_prob < 100; ilosc_prob++){
			int x = rand() % WYSOKOSC_;
			int y = rand() % SZEROKOSC_;
			int szer = rand() % 8 + 4;
			int wys = rand() % 8 + 4;
			Pokoj nowy(x, y, szer, wys);
			
			bool czy_pokoj_moze_powstac = true;
			if(nowy.czy_za_mapa() == false) czy_pokoj_moze_powstac = false;	
			
			if(lista_pokoi.empty()){
				if(czy_pokoj_moze_powstac == true){
					lista_pokoi.push_back(nowy);
					nowy.rysowanie_pokoju();
					break;
				}
			}
			
			else{
				for(size_t m = 0; m < lista_pokoi.size(); m++) {
					if(lista_pokoi[m].czy_sie_styka(nowy) == true){
					czy_pokoj_moze_powstac = false;
					break;	
				} 
			
				if(czy_pokoj_moze_powstac == true){
					lista_pokoi.push_back(nowy);
					nowy.rysowanie_pokoju();
					break;
				}	
			}
			}
		}
	}
	
	//rysowanie z pokoojami
	std::cout<< en;
	
	
	for(int i=0; i<WYSOKOSC_; i++){
		for(int j=0; j<SZEROKOSC_; j++) std::cout << plansza[i][j];
		std::cout << en;
	}
}
