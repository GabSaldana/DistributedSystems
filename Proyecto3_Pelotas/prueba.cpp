/* Para compilar use:
gcc gfxModified.c -c
gcc final_ukranio1.c -c
gcc final_ukranio1.o gfxModified.o -o final_ukranio1 -lX11 -lm

libreria original gfx:
https://www3.nd.edu/~dthain/courses/cse20211/fall2013/gfx/
Tomado de: https://github.com/PatMyron/slime-volleyball
Originally created by Patrick Myron and Anna McMahon
Further Modified by Ukranio Coronilla
*/

#include <stdio.h>
#include <math.h>
#include "gfxModified.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <vector>

//Resolución de la pantalla
#define ANCHURA 800
#define ALTURA 600

using namespace std;

class Ag{

public:

    Ag(float x=0, float y=0, float vx=0, float vy=0, int r=0, int *co=NULL);
    
    float getx(){ return x;printf("get\n");}
    float gety(){ return y;printf("get\n");}
    float getvx(){return vx;printf("get\n");}
    float getvy(){ return vy;printf("get\n");}
    int getr(){ return r;printf("get\n");}
    int getcolor(int i){return color[i];printf("get\n");}

    void setx(float X){x=X; printf("set\n");}
    void sety(float Y){y=Y;printf("set\n");}
    void setvx(float VX){vx=VX;printf("set\n");}
    void setvy(float VY){vy=VY;printf("set\n");}
    void setr(int R){r=R;printf("set\n");}
    void setcolor(int *co){
        color=co;printf("set\n");
    }

    void print(){

        printf("X:%f  Y:%f  VX:%f  VY:%f  R:%d \n",x,y,vx,vy,r);
        int i;
        for(i=0; i<3;i++)
            printf("%d,",color[i]);
        printf("\n");
    }


    friend void muevePelota(vector<Ag*>, Ag *pJugador);
    friend void checaColisiones(vector<Ag*>, Ag *pAgente);
    friend void mueveAgente(Ag *pJugador, bool tecla[6]);
    friend void validaMovimientoAgente(Ag *pAgente);
    friend void calculaDireccionPelota(Ag *Ball, Ag *Player);
    friend void dibujaPelota(vector<Ag*> );
    friend void dibujaPelotaAg(Ag *);
    friend void creaPelotas(int n);

private:

    float x;
    float y; //posicion
    
    float vx; //velocidad
    float vy;
    
    int r;  //radio
    int *color; //Color del agente

};

Ag::Ag(float X, float Y, float VX, float VY, int R, int *co){

    //cout << "Constructor" << endl;
    x=X;
    y=Y;
    r=R;
    vx=VX;
    vy=VY;
    
    color=co;

    return;
}

static vector<Ag*> pelotas;
bool tecla[6];  //Arreglo para saber si una tecla de dirección se ha presionado


int main()
{
     int color_agente[3]= {87,1,2};
    
    int j;

    for(j=0;j< 10 ; j++){
        float tam= 5*j;
        Ag pelota(ANCHURA/4, 500,0,0,tam,color_agente); 
        pelota.setx(ANCHURA/4);
        pelota.sety(500);
        pelota.setvx(0);
        pelota.setvy(0);
        pelota.setr(tam);
        pelotas.push_back(&pelota);
    }

    for(j=0;j< pelotas.size() ; j++){
        pelotas[j]->print();
    }
}



void muevePelota(vector<Ag*> v, Ag *pAgente){
    //Checa para ver si la pelota colisiona con algo para cambiar su velocidad    
    
    checaColisiones(v, pAgente);
    int i;
    for(i=0; i<v.size();i++){
    	printf("MUEVE_PELOTA\n");
    	//Ag *auxi=&v[i];

    	(v[i])->print();
    	float aux=(v[i])->getvy();
    	aux +=.08; //Para simular la aceleración de la gravedad
    	(v[i])->setvy(aux);
    	(v[i])->setx(((v[i])->getx()) + ((v[i])->getvx())); //Cambios para x recordando v=d/t 
    	(v[i])->sety(((v[i])->gety()) + ((v[i])->getvy()));	
    }
    
    gfx_clear();
}

//checa los bordes de la pelota y actualiza su localización, el vector velocidad   cambia si la pelota choca con algo.
void checaColisiones(vector<Ag*> v, Ag *pAgente){
    printf("COLISIONES\n");
    int i;
    for(i=0; i<v.size();i++){

    	//Ag *auxi=&v[i];

    	(v[i])->print();
    	float distContacto, agenteBolaDist;
    
    	if(((v[i])->getx() < (v[i])->getr()) || ((v[i])->getx() > (ANCHURA - (v[i])->getr()))){
        // colision lateral cambia al vector velocidad en x
        	float aux= -(v[i])->getvx();
        	(v[i])->setvx(aux);
    	}  
    	if((v[i])->y < (v[i])->r){

        	float aux= -(v[i])->getvy();
        	(v[i])->setvy(aux);
    	}   
    	if((v[i])->y >= (ALTURA - (v[i])->r)){

        	//colision en piso
        	float aux= -(v[i])->getvy();
        	(v[i])->setvy(aux);
    	}   
    	//distancia entre el centro del agente y la pelota
    	agenteBolaDist=sqrtf(powf(pAgente->gety() - (v[i])->gety(),2)+powf(pAgente->getx() - (v[i])->getx(),2));
    	//distancia minima permisible entre los centros del agente y la pelota
    	distContacto = pAgente->getr() + (v[i])->getr();
    	printf("distContacto= %f  agenteBolaDist = %f\n",distContacto,agenteBolaDist);
    	//checa para ver si existe colision entre la pelota y el agente
    	if(agenteBolaDist < distContacto)
        	calculaDireccionPelota((v[i]),pAgente);	
    }

}


//Lee el arreglo tecla para realizar un movimiento a la izquierda o a la derecha dependiendo de la tecla que se presionó.
void mueveAgente(Ag *pJugador, bool tecla[6]){

    printf("MUEVE_AGENTE\n");
    if ( tecla[3] == 1 ){  // Si se presionó la tecla de mover a la izquierda
        float aux=pJugador->getx();
        aux-=10;
        pJugador->setx(aux);
    }
    if ( tecla[5] == 1 ){  // Si se presionó la tecla de mover a la derecha
        float aux=pJugador->getx();
        aux+=10;
        pJugador->setx(aux);
    }
    gfx_flush();
}


//Después de que se ha presionado una tecla, la función se asegura que el agente no se ha salido de la pantalla
void validaMovimientoAgente(Ag *pAgente){
    
    printf("VALIDA_MOVIMIENTO_AG\n");
    //Limita al agente por la orilla derecha
    if((pAgente->getx())>(ANCHURA-pAgente->getr())){
        float aux=pAgente->getr();
        aux = ANCHURA - aux;
        pAgente->setx(aux);
    }
    //Limita al agente por la orilla izquierda
    if((pAgente->getx())<(pAgente->getr())){
        float aux=pAgente->getr();
        pAgente->setx(aux);
    }
    
}//end func


//Cambia la dirección de la pelota de acuerdo a las leyes de la física
void calculaDireccionPelota(Ag *Bola, Ag *Jugador){ 
    //la velocidad absoluta de la pelota se inicializa a 10 después de que choca con la raqueta debido
    //a que de no hacerlo se movería mas lento cada vez
    printf("CALCULA DIRECCION\n");
    float velocidadAbsoluta = 10;
    float pendienteEntreCentros;
    float difCentrosX,difCentrosY;
    float anguloEntreCentros;

    difCentrosX = Bola->getx() - Jugador->getx();
    difCentrosY = Bola->gety() - Jugador->gety();
    //Aunque puede existir un denominador igual a cero, y pendiente infinita la función arco tangente si resuelve con argumento infinito
    pendienteEntreCentros = difCentrosY / difCentrosX ;
    anguloEntreCentros = atanf(pendienteEntreCentros);
    if(difCentrosX < 0 && difCentrosY < 0)
        anguloEntreCentros += acosf(-1.0); // Ajusta la restricción del angulo sumandole PI = 3.14159...
            
    float aux1=velocidadAbsoluta * cosf(anguloEntreCentros);
    float aux2= velocidadAbsoluta * sinf(anguloEntreCentros);
    Bola->setvx(aux1);
    Bola->setvy(aux2);
}

void dibujaPelota(vector<Ag*> v){
    //Dibuja la pelota
        printf("DIBUJA  PELOTA\n");
        //pelota->print();
        int i;
        for(i=0;i<v.size();i++){
        	//Ag *auxi=&v[i];
        	gfx_color(v[i]->getcolor(0),v[i]->getcolor(1),v[i]->getcolor(2));
        	gfx_fill_arc(v[i]->getx() - v[i]->getr(), v[i]->gety() - v[i]->getr(), 2*v[i]->getr(), 2*v[i]->getr(), 0, 360*64);
        }
}

void dibujaPelotaAg(Ag *jugador){
    //Dibuja al jugador 
        gfx_color(jugador->getcolor(0),jugador->getcolor(1),jugador->getcolor(2));
        gfx_fill_arc(jugador->getx() - jugador->getr(), jugador->gety() - jugador->getr(), 2*jugador->getr(), 2*jugador->getr(), 0, 180*64);    
}



