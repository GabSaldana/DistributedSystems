#ifndef __PACKDGRAM
#define __PACKDGRAM

#include <cstring>

class PaqueteDatagrama {
	public: 
		PaqueteDatagrama(char *,unsigned int, char*,int);
		PaqueteDatagrama(unsigned int);
		~PaqueteDatagrama();
		char* obtieneDireccion();
		unsigned int obtieneLongitud();
		int obtienePuerto();
		char *obtieneDatos();
		void inicializaPuerto(int);
		void inicializaIp(char *);
		void inicializaDatos(char *);

	private:
		char *datos;			//Almacena los datos
		unsigned int longitud;	//Almacena la longitude de la cadena de datos
		char ip[17];			//Almacena la IP
		int puerto;				//Almacena el puerto
};

#endif
