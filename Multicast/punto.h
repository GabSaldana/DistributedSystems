/* CABECERA PARA LA ESTRUCTURA DE UN PUNTO*/
#include <inttypes.h>

// Opciones de figuras
#define TRIANGULO 3 
#define CUADRADO  4 
#define PENTAGONO 5
#define MAX  5

typedef struct {
  int x;
  int y;
} punto;

typedef struct{

	int figura;//figuras definidas
	punto puntos[MAX];
} figura_pac;