#include <iostream>
#include <conio2.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
using namespace std;
//------------------------------------------------------------------------------//
//---------------------------------Variables------------------------------------//
//------------------------------------------------------------------------------//
const int eje_X = 50;
const int eje_Y = 25;

const int disparos = 500000;
const int enemigos = 75;
const int disparos_enemigos = 50;

bool iniciar = false;

string enemigo_1 = "W";
string enemigo_2 = "H";
string enemigo_3 = "M";

struct disparo{
	int x; 
	int y;
	bool activo;
};

struct disparo_enemigo{
	int x; 
	int y;
	bool activo;
};

struct enemigo{
	int x; 
	int y;
	int type;
	bool activo;
};

int nave = eje_X/2;
int vida = 3;
int punto = 0;

disparo Disparo[disparos];
int jugador_disparo = 0;

enemigo Enemigo[enemigos];
int nave_enemiga = 25;

disparo_enemigo DisparoEnemigo[disparos_enemigos];
int disparo_nave_enemiga = disparos_enemigos;

int Disparo_Enemigo = 1;
//------------------------------------------------------------------------------//
//--------------------------Menu de Inicio--------------------------------------//
//------------------------------------------------------------------------------//
void Pantalla_Inicial(){

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
	int izquierda = (a - text[i].length()-2)/2;
	int derecha = a-text[i].length() -2 -izquierda;
	
	cout << "*"; 
	
	for(int j = 0; j < izquierda; j++){
		cout << " ";
	}
	cout << text[i];
	
	for(int j = 0; j < derecha; j++){
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

iniciar = true;
}

//------------------------------------------------------------------------------//
//-------------------------Pantalla cuando Ganas--------------------------------//
//------------------------------------------------------------------------------//
void Pantalla_Ganadora(string p){
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
		int izquierda = (a - text[i].length()-2)/2;
		int derecha = a-text[i].length() -2 -izquierda;
		
		cout << "*"; 
		
		for(int j = 0; j < izquierda; j++){
			cout << " ";
		}
		cout << text[i];
		
		for(int j = 0; j < derecha; j++){
			cout << " ";
		}
		cout << "*" << endl;
	}
	
	for(int i = 0; i < a; i++){
		cout << "*"; 
	}
	cout << endl;
}

//------------------------------------------------------------------------------//
//------------------------Pantalla cuando Pierdes-------------------------------//
//------------------------------------------------------------------------------//
void Pantalla_Perdedora(string p){
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
		int izquierda = (a - text[i].length()-2)/2;
		int derecha = a-text[i].length() -2 -izquierda;
		
		cout << "*"; 
		
		for(int j = 0; j < izquierda; j++){
			cout << " ";
		}
		cout << text[i];
		
		for(int j = 0; j < derecha; j++){
			cout << " ";
		}
		cout << "*" << endl;
	}
	
	for(int i = 0; i < a; i++){
		cout << "*"; 
	}
	cout << endl;
}
	
//------------------------------------------------------------------------------//
//-------------------------Clase que inicia los dibujos-------------------------//
//------------------------------------------------------------------------------//
void dibujos(){
	clrscr();
	
	for(int i = 0; i < eje_Y; i++){
		for(int j = 0 ; j < eje_X; j++){
			bool borde = (i==0 || i == eje_Y-1 || j == 0 || j == eje_X-1 );
			bool mostrar = false;
			
			if(borde){
				cout << "*";
				mostrar = true;
			}
			if(!mostrar){
				for(int k=0; k<jugador_disparo; k++){
					if(Disparo[k].activo && Disparo[k].x==j && Disparo[k].y==i){
						textcolor(GREEN);
						cprintf("|");
						textcolor(WHITE);
						mostrar = true;
						break;
					}
				}
			}
			if(!mostrar){
				for(int k=0; k<disparo_nave_enemiga; k++){
					if(DisparoEnemigo[k].activo && DisparoEnemigo[k].x==j && DisparoEnemigo[k].y==i){
						textcolor(RED);
						cprintf("v");
						textcolor(WHITE);
						mostrar = true;
						break;
					}
				}
			}
			
			if(!mostrar){
				for(int k=0; k<nave_enemiga; k++){
					if(Enemigo[k].activo && Enemigo[k].x==j && Enemigo[k].y==i-2){
						textcolor(RED);
						if(Enemigo[k].type == 3) cout <<enemigo_3;
						textcolor(LIGHTRED);
						if(Enemigo[k].type == 2) cout <<enemigo_2;
						textcolor(YELLOW);
						if(Enemigo[k].type == 1) cout <<enemigo_1;
						textcolor(WHITE);
						mostrar = true;
						break;
					}
				}
			}
			
			if(!mostrar){
				if(i==eje_Y-2 && j==nave){
					textcolor(BLUE);
					cprintf("A");
					textcolor(WHITE);
					mostrar = true;
				}
			}
			if(!mostrar)
			   cout << " ";
		}
		cout << endl;
	}
	cout << "Vidas: " << vida << " Puntos: " << punto << endl;
}
	
//------------------------------------------------------------------------------//
//-------------------------Clase que inicia a los enemigos----------------------//
//------------------------------------------------------------------------------//
void Iniciar_Enemigos(){
	nave_enemiga = 0;
	for(int j=4; j<eje_X-15 ; j+=3){
		Enemigo[nave_enemiga].x = j;
		Enemigo[nave_enemiga].y = 1;
		Enemigo[nave_enemiga].activo = true;
		Enemigo[nave_enemiga].type = 3;
		nave_enemiga++;
	}
	for(int j=4; j<eje_X-15 ; j+=3){
		Enemigo[nave_enemiga].x = j;
		Enemigo[nave_enemiga].y = 2;
		Enemigo[nave_enemiga].activo = true;
		Enemigo[nave_enemiga].type = 2;
		nave_enemiga++;
	}
	for(int j=4; j<eje_X-15 ; j+=3){
		Enemigo[nave_enemiga].x = j;
		Enemigo[nave_enemiga].y = 3;
		Enemigo[nave_enemiga].activo = true;
		Enemigo[nave_enemiga].type = 1;
		nave_enemiga++;
	}
}
	
	
//------------------------------------------------------------------------------//
//-------------------------Clase que mueve al jugador---------------------------//
//------------------------------------------------------------------------------//
void Mover_Jugador(char tecla){
	if(tecla=='a' && nave>1) nave--;
	if(tecla=='d' && nave<eje_X-2) nave++;
	if(tecla==' ' && jugador_disparo < disparos){
		Disparo[jugador_disparo].x = nave;
		Disparo[jugador_disparo].y = eje_Y-3;
		Disparo[jugador_disparo].activo = true;
		jugador_disparo++;
	}
}
	
//------------------------------------------------------------------------------//
//--------------Clase que mueve los disparos del jugado-------------------------//
//------------------------------------------------------------------------------//
void Mover_Disparos(){
	for(int k=0; k<jugador_disparo; k++){
		if(Disparo[k].activo){
			Disparo[k].y--;
			if(Disparo[k].y<=0) Disparo[k].activo = false;
			
			for(int m=0; m < nave_enemiga; m++){
				if(Enemigo[m].activo && Enemigo[m].x==Disparo[k].x && Enemigo[m].y==Disparo[k].y ){
					Enemigo[m].activo = false;
					Disparo[k].activo = false;
					
					if(Enemigo[m].type == 1){
						punto += 100;
					}
					if(Enemigo[m].type == 2){
						punto += 200;
					}
					if(Enemigo[m].type == 3){
						punto += 300;
					}
					
				}
			}
		}
	}
}
	
//------------------------------------------------------------------------------//
//------------------Clase que mueve a los enemigos------------------------------//
//------------------------------------------------------------------------------//
void Mover_Enemigos(){
	int minX = eje_X, maxX=0;
	for(int k=0; k<nave_enemiga; k++){
		if(Enemigo[k].activo){
			if(Enemigo[k].x<minX) minX = Enemigo[k].x;
			if(Enemigo[k].x>maxX) maxX = Enemigo[k].x;
		}
	}
	
	if(maxX+Disparo_Enemigo >= eje_X-1 || minX+Disparo_Enemigo <= 1){
		Disparo_Enemigo *= -1;
		for(int k=0; k<nave_enemiga; k++){
			if(Enemigo[k].activo) Enemigo[k].y++;
		}
	}
	
	for(int k=0; k<nave_enemiga; k++){
		if(Enemigo[k].activo) Enemigo[k].x += Disparo_Enemigo;
	}
	
	for(int k=0; k<nave_enemiga; k++){
		if(Enemigo[k].activo && Enemigo[k].y >= eje_Y-4){
			vida = 0;
			return;
		}
	}
	
}
	
//------------------------------------------------------------------------------//
//---------------------Clase que mueve los disparos enemigos--------------------//
//------------------------------------------------------------------------------//
void Mover_Disparos_Enemigos(){
	for(int i = 0; i < disparo_nave_enemiga; i++){
		if(DisparoEnemigo[i].activo){
			DisparoEnemigo[i].y++;
			if(DisparoEnemigo[i].y >= eje_Y-1){
				DisparoEnemigo[i].activo = false;
			}
		}
	}
}
	
//------------------------------------------------------------------------------//
//----------------------Clase que inicia los disparos enemigos------------------//
//------------------------------------------------------------------------------//
void Iniciar_Disparos_Enemigos(){
	for(int i = 0; i<disparo_nave_enemiga; i++){
		DisparoEnemigo[i].activo = false;
	}
}
	
//------------------------------------------------------------------------------//
//--------------------------Clase que controla las colisiones-------------------//
//------------------------------------------------------------------------------//
void Colisiones(){
	for(int i = 0; i<disparo_nave_enemiga; i++){
		if(DisparoEnemigo[i].activo && DisparoEnemigo[i].x == nave && DisparoEnemigo[i].y == eje_Y-2){
			vida--;
			punto -= 150;
			DisparoEnemigo[i].activo = false;
		}
	}
}
	
//------------------------------------------------------------------------------//
//----------------------------Clase que controla el fin del juego---------------//
//------------------------------------------------------------------------------//
bool Fin_del_Juego(){
	if(vida == 0) return true;
	bool hayVivos = false;
	for(int k=0; k<nave_enemiga; k++){
		if(Enemigo[k].activo){
			hayVivos = true;
			break;
		}
	}
	return !hayVivos;
}
	
//------------------------------------------------------------------------------//
//------------------------Clase que inicia todas las clases---------------------//
//------------------------------------------------------------------------------//
int main() {
	srand(time(0));	
	
	Pantalla_Inicial();
	if(iniciar){
		Iniciar_Enemigos();
		Iniciar_Disparos_Enemigos();
		
		while(!Fin_del_Juego()){
			if(kbhit()){
				char tecla = getch();
				Mover_Jugador(tecla);
			}
			Mover_Disparos();
			Mover_Enemigos();
			
			if(rand()%10 == 0){
				int k = rand() % nave_enemiga;
				if(Enemigo[k].activo){
					for(int i=0; i<disparo_nave_enemiga; i++){
						if(!DisparoEnemigo[i].activo){
							DisparoEnemigo[i].x = Enemigo[k].x;
							DisparoEnemigo[i].y = Enemigo[k].y +1;
							DisparoEnemigo[i].activo = true;
							break;
						}
					}
				}
			}
			
			Mover_Disparos_Enemigos();
			Colisiones();
			
			dibujos();
			Sleep(100);
		}
		
		string p = to_string(punto);
		if(vida == 0){
			Pantalla_Perdedora(p);
		}else{
			Pantalla_Ganadora(p);
		}
		
		char tecla;
		do{
			tecla = getch();		
		} while(tecla != 'e');
		
	}
	return 0;
}	
