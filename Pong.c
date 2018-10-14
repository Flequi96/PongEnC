//Pong v0.01

#include <stdio.h>
#include <windows.h>
#define V 21
#define H 75

void inicio(char campo[V][H], int pelX, int pelY, int inijug, int finjug, int iniia, int finia);
void borde (char campo[V][H]);
void racjug(char campo[V][H], int inijug, int finjug);
void raqia(char campo[V][H], int iniia, int finia);
void pel(char campo[V][H], int pelX, int pelY);
void leercamp(char campo[V][H]);
void gameloop(char campo[V][H], int pelX, int pelY, int inijug, int finjug, int iniia, int finia,int modX, int modY, int modia);
void draw(char campo[V][H]);
void input(char campo[V][H], int *pelX, int *pelY, int *inijug, int *finjug, int *iniia, int *finia, int *modX, int *modY, int *modia, int *gol);
void update(char campo[V][H], int pelX, int pelY, int inijug, int finjug, int iniia, int finia);
void gotoxy(int x, int y);

int main(){
	
	int pelX,pelY, inijug,finjug, iniia,finia; //Posicion
	int modX,modY,modia;  //Modificacion
	char campo[V][H];
	
	
	//Posicion
	pelX = 37;
	pelY = 10;
	
	inijug = 8;
	finjug = 12;
	
	iniia = 5;
	finia = 18;
	
	//Modificacion
	modX = -1;
	modY = -1;
	
	modia = -1;
	
	
	
	inicio(campo, pelX,pelY,inijug,finjug,iniia,finia);
	
	gameloop(campo,pelX,pelY,inijug,finjug,iniia,finia,modX,modY,modia);
	
	
	system("pause");
	return 0;	
	

}

void inicio(char campo[V][H], int pelX, int pelY, int inijug, int finjug, int iniia, int finia){
	borde(campo);
	racjug(campo,inijug,finjug);
	raqia(campo,iniia,finia);
	pel(campo,pelX,pelY);
		
}

void borde (char campo[V][H]){
	int i,j;
	
	for(i = 0; i< V; i++){
		for(j = 0; j < H; j++){
			if(i == 0 || i == V-1){
				campo[i][j] = '-';
			}else if(j == 0 || j == H-1){
				campo[i][j] = '|';
			}else{
				campo[i][j] = ' ';
			}
		}
	}
}

void racjug(char campo[V][H], int inijug, int finjug){
	int i,j;
	
	for(i=inijug; i<=finjug;i++){
		for(j=2; j<=3; j++){
			campo[i][j] = 'X';
		}
	}
	
}


void raqia(char campo[V][H], int iniia, int finia){
	int i,j;
	
	for(i = iniia; i<= finia; i++){
		for(j = H-4; j<= H-3; j++){
			campo[i][j] = 'X';
		}
	}
	
}

void pel(char campo[V][H], int pelX, int pelY){
	campo[pelY][pelX] = 'O';
}

void leercamp(char campo[V][H]){
	int i,j;
	
	for(i = 0; i < V; i++){
		for(j=0;j<H;j++){
			printf("%c", campo[i][j]);		
		}
		printf("\n");	
	}
}

void gameloop(char campo[V][H], int pelX, int pelY, int inijug, int finjug, int iniia, int finia,int modX, int modY, int modia){
	int gol;
	gol = 0;
	
	do{
		draw(campo); //Dibujar en pantalla
		input(campo,&pelX,&pelY,&inijug,&finjug,&iniia,&finia,&modX,&modY,&modia,&gol); // Verificar y modificar las posiciones
		update(campo, pelX,pelY,inijug,finjug,iniia,finia); //Actualizar la matriz campo
		
		Sleep (10);
		
	}while(gol == 0);

}

void draw(char campo[V][H]){
	gotoxy(0,0);
	leercamp(campo);

}

void input(char campo[V][H], int *pelX, int *pelY, int *inijug, int *finjug, int *iniia, int *finia, int *modX, int *modY, int *modia, int *gol){
	int i;
	char key;
	
	//Verificacion
	if(*pelY == 1 || *pelY == V-2){
		*modY *= -1;
	}
	
	if(*pelX == 1 || *pelX == H-2){
		*gol = 1;
	}
	
	if(*pelX == 4){
		
		for(i = (*inijug); i <= (*finjug); i++){
			if(i == (*pelY)){
				*modX *= -1;
			}
		}
	}
	
	if(*pelX == H -5){
		for(i = (*iniia); i<= (*finia); i++){
			if(i == (*pelY)){
				*modX *= -1;
			}
		}
	
	}
	
	if(*iniia == 1 || *finia == V-1){
		*modia *= -1;	
	}
	
	//Modificacion
	
	if(*gol == 0){
	//Pelota:
		*pelX += (*modX);
		*pelY += (*modY);
		
	//Raqueta de la ia:
		*iniia += (*modia);
		*finia += (*modia);
		
	//Raqueta del jugador
		if(kbhit() == 1){ 
			key = getch(); // Lo mismo que scanf pero sin pulsar intro
			
			if(key == '8'){
				if(*inijug != 1){
					*inijug -= 1;
					*finjug -= 1;
				}
			}
			
			if(key == '2'){
				if(*finjug != V-2){
					*inijug +=1;
					*finjug += 1;
				}
			}
		}
	}
	

}

void update(char campo[V][H], int pelX, int pelY, int inijug, int finjug, int iniia, int finia){
	borde(campo);
	racjug(campo,inijug,finjug);
	raqia(campo,iniia,finia);
	pel(campo,pelX,pelY);	
}

void gotoxy(int x, int y)  { 
     COORD coord; 
     coord.X=x; 
     coord.Y=y; 
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); 
}
