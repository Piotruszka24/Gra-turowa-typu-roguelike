#include <iostream>

#define en '\n'

char plansza[20][50];

int main(){
	for(int i=0; i<20; i++){
		for(int j=0; j<50; j++) plansza[i][j]= char(219);//char(178);'-';
	}
	
	for(int i=0; i<20; i++){
		for(int j=0; j<50; j++) std::cout << plansza[i][j];
		std::cout << en;
	}
}
