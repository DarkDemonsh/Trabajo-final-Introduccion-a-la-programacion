#include <iostream>
#include <conio2.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
using namespace std;

const int X = 50;
const int Y = 25;

const int shooter = 500000;
const int enemir = 75;

bool init = false;

string e1 = "W";
string e2 = "H";
string e3 = "M";

struct shoot{
	int x; 
	int y;
	bool act;
};

struct enemi{
	int x; 
	int y;
	int type;
	bool act;
};

int nave = X/2;
int vida = 3;
int punto = 0;

shoot disp[shooter];
int ns = 0;
enemi enemis[enemir];
int ne = 25;

int denemi = 1;

void inicio(){
	cout << "Acaba con las naves enemigas antes de que lleguen abajo" << endl;
	cout << " " << endl;
	cout << "Muevete con 'A' para ir a la izquierda, 'D' para ir a la derecha" << endl;
	cout << " " << endl;
	cout << "Dispara con 'BARRA ESPACIADORA'" << endl;
	cout << " " << endl;
	cout << "Presiona 'P' para iniciar" << endl;
	
	char tecla;
	do{
		tecla = getch();
		
	} while(tecla != 'p');
	
		init = true;
}

void dibujos(){
	clrscr();
	
	for(int i = 0; i < Y; i++){
		for(int j = 0 ; j < X; j++){
			bool borde = (i==0 || i == Y-1 || j == 0 || j == X-1 );
			bool show = false;
			
			if(borde){
				cout << "*";
				show = true;
			}
			if(!show){
				for(int k=0; k<ns; k++){
					if(disp[k].act && disp[k].x==j && disp[k].y==i){
						textcolor(GREEN);
						cprintf("|");
						textcolor(WHITE);
						show = true;
						break;
					}
				}
			}
			if(!show){
				for(int k=0; k<ne; k++){
					if(enemis[k].act && enemis[k].x==j && enemis[k].y==i-2){
						textcolor(RED);
						if(enemis[k].type == 3) cout <<e3;
						textcolor(LIGHTRED);
						if(enemis[k].type == 2) cout <<e2;
						textcolor(YELLOW);
						if(enemis[k].type == 1) cout <<e1;
						textcolor(WHITE);
						show = true;
						break;
					}
				}
			}

			if(!show){
				if(i==Y-2 && j==nave){
					textcolor(BLUE);
					cprintf("A");
					textcolor(WHITE);
					show = true;
				}
			}
			if(!show)
			   cout << " ";
		}
		cout << endl;
	}
	cout << "Vidas: " << vida << " Puntos: " << punto << endl;
}
	
	void initE(){
		ne = 0;
			for(int j=4; j<X-15 ; j+=3){
				enemis[ne].x = j;
				enemis[ne].y = 1;
				enemis[ne].act = true;
				enemis[ne].type = 3;
				ne++;
			}
			for(int j=4; j<X-15 ; j+=3){
				enemis[ne].x = j;
				enemis[ne].y = 2;
				enemis[ne].act = true;
				enemis[ne].type = 2;
				ne++;
			}
			for(int j=4; j<X-15 ; j+=3){
				enemis[ne].x = j;
				enemis[ne].y = 3;
				enemis[ne].act = true;
				enemis[ne].type = 1;
				ne++;
			}
		}
		
		
		void movN(char tecla){
			if(tecla=='a' && nave>1) nave--;
			if(tecla=='d' && nave<X-2) nave++;
			if(tecla==' ' && ns < shooter){
				disp[ns].x = nave;
				disp[ns].y = Y-3;
				disp[ns].act = true;
				ns++;
			}
		}
			
			void movS(){
				for(int k=0; k<ns; k++){
					if(disp[k].act){
						disp[k].y--;
						if(disp[k].y<=0) disp[k].act = false;
						
						for(int m=0; m < ne; m++){
							if(enemis[m].act && enemis[m].x==disp[k].x && enemis[m].y==disp[k].y ){
								enemis[m].act = false;
								disp[k].act = false;
								
								if(enemis[m].type == 1){
									punto += 100;
								}
								if(enemis[m].type == 2){
									punto += 200;
								}
								if(enemis[m].type == 3){
									punto += 300;
								}
								
							}
						}
					}
				}
			}
				
				void movE(){
					int minX = X, maxX=0;
					for(int k=0; k<ne; k++){
						if(enemis[k].act){
							if(enemis[k].x<minX) minX = enemis[k].x;
							if(enemis[k].x>maxX) maxX = enemis[k].x;
						}
					}
					
					if(maxX+denemi >= X-1 || minX+denemi <= 1){
						denemi *= -1;
						for(int k=0; k<ne; k++){
							if(enemis[k].act) enemis[k].y++;
						}
					}
					
					for(int k=0; k<ne; k++){
						if(enemis[k].act) enemis[k].x += denemi;
					}
					
					for(int k=0; k<ne; k++){
						if(enemis[k].act && enemis[k].y >= Y-4){
							vida--;
							if(vida > 0){
								for(int k=0; k<ne; k++){
									enemis[k].y = 2 + (k/10);
									enemis[k].x = 3 + (k%10)*2;
								}
							}
							return;
						}
					}
					
				}
					
					bool END(){
						if(vida == 0) return true;
						bool hayVivos = false;
						for(int k=0; k<ne; k++){
							if(enemis[k].act){
								hayVivos = true;
								break;
							}
						}
						return !hayVivos;
					}
						
						int main() {
							srand(time(0));	
							
						inicio();
						if(init){	
							initE();
							
							while(!END()){
								if(kbhit()){
									char tecla = getch();
									movN(tecla);
								}
								movS();
								movE();
								
								dibujos();
								Sleep(100);
							}
							clrscr();
							if(vida == 0){
								cout << "PERDISTE" << endl;
							}else{
								cout << "GANASTE" << endl;	
							}
							cout << " " << endl;
							cout << "PUNTUACION: " << punto << endl;
							cout << " " << endl;
							cout << "Presiona 'E' para salir" << endl;
							char tecla;
							do{
								tecla = getch();		
							} while(tecla != 'e');
							
						}
						return 0;
						}	
