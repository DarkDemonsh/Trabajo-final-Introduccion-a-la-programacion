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
const int eshooter = 50;

bool init = false;

string e1 = "W";
string e2 = "H";
string e3 = "M";

struct shoot{
	int x; 
	int y;
	bool act;
};

struct eshoot{
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
eshoot edisp[eshooter];
int ens = eshooter;

int denemi = 1;

void inicio(){

string text[]{
"Alumno: Pablo A Aguilar",
"DNI: 42.165.351",
" ",
"Acaba con las naves enemigas antes de que lleguen abajo",
"Presiona con 'A' para ir a la izquierda",
"Presiona con 'D' para ir a la derecha",
"Dispara con 'BARRA ESPACIADORA'",
" ",
"Presiona 'P' para iniciar"
};					
	int ln = sizeof(text)/sizeof(text[0]);

	int a = 0;
	for(int i = 0; i < ln; i++){
	if(text[i].length() > a){
		a = text[i].length();
	}
	}	
	a += 4;

	for(int i = 0; i < a; i++){
		cout << "*"; 
	}
	cout << endl;
	
	for(int i = 0; i < ln; i++){
		int iz = (a - text[i].length()-2)/2;
		int dr = a-text[i].length() -2 -iz;
		
		cout << "*"; 
		
		for(int j = 0; j < iz; j++){
			cout << " ";
		}
		cout << text[i];
		
		for(int j = 0; j < dr; j++){
		cout << " ";
		}
		cout << "*" << endl;
	}
	
	for(int i = 0; i < a; i++){
		cout << "*"; 
	}
	cout << endl;

	char tecla;
	do{
		tecla = getch();
		
	} while(tecla != 'p');
	
		init = true;
}

void ganar(string p){
	string text[]{
	"GANASTE",
	" ",	
	" ",
	"PUNTUACION: ",
	p,
	" ",
	"Presiona 'E' para salir",
	};					
	int ln = sizeof(text)/sizeof(text[0]);
	
	int a = 0;
	for(int i = 0; i < ln; i++){
		if(text[i].length() > a){
			a = text[i].length();
		}
	}	
	a += 4;
	
	for(int i = 0; i < a; i++){
		cout << "*"; 
	}
	cout << endl;
	
	for(int i = 0; i < ln; i++){
		int iz = (a - text[i].length()-2)/2;
		int dr = a-text[i].length() -2 -iz;
		
		cout << "*"; 
		
		for(int j = 0; j < iz; j++){
			cout << " ";
		}
		cout << text[i];
		
		for(int j = 0; j < dr; j++){
			cout << " ";
		}
		cout << "*" << endl;
	}
	
	for(int i = 0; i < a; i++){
		cout << "*"; 
	}
	cout << endl;
}

void perder(string p){
		string text[]{
		"PERDISTE",
		" ",	
		" ",
		"PUNTUACION: ",
		p,
		" ",
		"Presiona 'E' para salir",
		};					
		int ln = sizeof(text)/sizeof(text[0]);
		
		int a = 0;
		for(int i = 0; i < ln; i++){
			if(text[i].length() > a){
				a = text[i].length();
			}
		}	
		a += 4;
		
		for(int i = 0; i < a; i++){
			cout << "*"; 
		}
		cout << endl;
		
		for(int i = 0; i < ln; i++){
			int iz = (a - text[i].length()-2)/2;
			int dr = a-text[i].length() -2 -iz;
			
			cout << "*"; 
			
			for(int j = 0; j < iz; j++){
				cout << " ";
			}
			cout << text[i];
			
			for(int j = 0; j < dr; j++){
				cout << " ";
			}
			cout << "*" << endl;
		}
		
		for(int i = 0; i < a; i++){
			cout << "*"; 
		}
		cout << endl;
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
				for(int k=0; k<ens; k++){
					if(edisp[k].act && edisp[k].x==j && edisp[k].y==i){
						textcolor(RED);
						cprintf("v");
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
							vida = 0;
							return;
						}
					}
					
				}
					
					void mde(){
						for(int i = 0; i < ens; i++){
							if(edisp[i].act){
								edisp[i].y++;
								if(edisp[i].y >= Y-1){
									edisp[i].act = false;
								}
							}
						}
					}
						
					void initde(){
						for(int i = 0; i<ens; i++){
							edisp[i].act = false;
						}
					}
						
					void hit(){
						for(int i = 0; i<ens; i++){
							if(edisp[i].act && edisp[i].x == nave && edisp[i].y == Y-2){
								vida--;
								punto -= 150;
								edisp[i].act = false;
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
							initde();
							
							while(!END()){
								if(kbhit()){
									char tecla = getch();
									movN(tecla);
								}
								movS();
								movE();
								
								if(rand()%10 == 0){
									int k = rand() % ne;
									if(enemis[k].act){
									for(int i=0; i<ens; i++){
										if(!edisp[i].act){
											edisp[i].x = enemis[k].x;
											edisp[i].y = enemis[k].y +1;
											edisp[i].act = true;
											break;
										}
									}
									}
								}

								mde();
								hit();
								
								dibujos();
								Sleep(100);
							}
							clrscr();
							string p = to_string(punto);
							if(vida == 0){
								perder(p);
							}else{
								ganar(p);
							}
							
							char tecla;
							do{
								tecla = getch();		
							} while(tecla != 'e');
							
						}
						return 0;
						}	
