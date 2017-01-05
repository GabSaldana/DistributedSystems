#include <bits/stdc++.h>
#include "SocketDatagrama.h"

using namespace std;

const int MAXL = 3;
const int PETICION = 1;
const int LIBRE = 2;
const int RESULTADO = 3;
const int MAESTRO = 4;
const int CLIENTE = 5;


const int PUERTO = 8200;

class Token
{
	public:
		string value;
    private:
        friend ostream& operator<<(ostream&,Token const&);
        friend istream& operator>>(istream&,Token&);
        
};

istream& operator>>(istream& str,Token& data){
    if (!str){   
    	return str;
    }

    char    x;
    do
    {
        x = str.get();
    }
    while(str && isspace(x) && (x != '\n'));

    if (!str)
    {
        return str;
    }
    data.value  ="";

    if (x == '\n')
    {   data.value  = "";
        return str;
    }
    str.unget();
    str >> data.value;

    return str;
}


vector <string> nombreLibros;
vector <int> libros[MAXL];
vector <string> infLibros[MAXL];
unordered_map<string, int> hasheo;
int lastvalue, posicion;
int AA = -1, BB;

char clienteIP[16];
int clientePuerto;

vector < string > IPS;
char auxIP[16];

SocketDatagrama sock(PUERTO);
set <int> res;


void GeneraNombresLibros(){
	string nombre;
	//prueba
	
	/*nombre = "A.txt";
	nombreLibros.push_back(nombre);

	nombre = "B.txt";
	nombreLibros.push_back(nombre);*/

	//fin prueba



	nombre = "Bestiario-Julio_Cortazar.txt";
	nombreLibros.push_back(nombre);
	nombre = "Demian-Hermann_Hesse.txt";
	nombreLibros.push_back(nombre);
	nombre = "Dioses_Y_Heroes_De_La_Antigua_Grecia-Robert_Graves.txt";
	nombreLibros.push_back(nombre);
	nombre = "El_Amante-Marguerite_Duras.txt";
	nombreLibros.push_back(nombre);
	nombre = "El_hombre_en_busca_de_sentido-Viktor_Frankl.txt";
	nombreLibros.push_back(nombre);
	nombre = "Territorio_comanche-Arturo_Perez_Reverte.txt";
	nombreLibros.push_back(nombre);
	nombre = "Una_mujer_endemoniada-Jim_Thompson.txt";
	nombreLibros.push_back(nombre);
	nombre = "Una_navidad_diferente-John_Grisham.txt";
	nombreLibros.push_back(nombre);

}

void AgregaPalabras(vector<int>& palabras, int pos, vector <string>& info){
	ifstream   f(nombreLibros[pos]);
	Token x;
	while(f >> x){
		string aux = x.value;
		if(aux.size() == 0) continue;
		info.push_back(aux);
		if(hasheo.find(aux) == hasheo.end())
			hasheo[aux] = ++lastvalue;

		palabras.push_back(hasheo[aux]); 
    }
}


void MejorRespuesta(pair <int, int> x, vector <pair <int, int> >& respuestas, int& maxTam){
	if(maxTam < x.second - x.first + 1){
		respuestas.clear();
		respuestas.push_back(x);
		maxTam = x.second - x.first + 1;
	}else if(maxTam == x.second - x.first + 1){
		respuestas.push_back(x);
	}
}


vector< pair<int, int> > ConsultaPalabra(int A, int B){
	vector < pair <int, int> > respuestas;
	int N = libros[A].size();
	int M = libros[B].size();

	int maxTam = -1;
	
	for(int x = 0; x < N; x++){

		int maxAns = 0;
		for(int i = 0; i < M; i++){
			int tam = 0;
			while(x + tam < N && tam + i < M && libros[A][x + tam] == libros[B][i + tam])
				tam++;
			if(maxAns < tam){
				maxAns = tam;
				MejorRespuesta(make_pair(x, x + maxAns - 1), respuestas, maxTam);
			}
		}
	}
	return respuestas;
}



int ISMAESTRO = 1;


vector <pair <int, int> > respuestasLibro[MAXL * MAXL];

void GuardarRespuestas(pair <int, int> x, int libro){
	respuestasLibro[libro].push_back(x);
}


void ImprimeRespuesta(vector < pair <int, int> > x, int A, int B){
	cout << "\n\nCadena(s) entre el archivo " << nombreLibros[A] << " y " << nombreLibros[B] << " con el mayor número de tokens (" << x.size() << "):" << endl;
	for(int i = 1; i <= x.size(); i++){
		cout << "CADENA " << i << ": <";
		for(int j = x[i - 1].first; j <= x[i - 1].second; j++){
			cout << infLibros[A][j] << " ";
		}
		cout << ">\n";
	}
}

void* Maestro(void*){
	while(1){
		if(!ISMAESTRO) continue;
		if(AA == -1)
			continue;
		if(AA + 1 >= MAXL){
			//if(cont == (MAXL * (MAXL - 1)) / 2){
			
			//}
			//cout << "Ya acabe" << endl;
			break;
		}
		int* num = new int[4];
		num[0] = LIBRE;
		for(auto i : IPS){
			sprintf(auxIP, "%s", i.c_str());
			PaqueteDatagrama paks((char *) num, 16, auxIP, PUERTO);
			sock.envia(paks);
		}

		sleep(1);
	}
}

int TRABAJO = 0;
int pos, LibroA, LibroB;



void* Trabajo(void*){
	while(1){
		if(res.size() == (MAXL * (MAXL - 1)) / 2){
			sleep(3);
			for(int i = 0; i < MAXL; i++){
				for(int j = i + 1; j < MAXL; j++){
					ImprimeRespuesta(respuestasLibro[i * MAXL + j], i, j);
				}
			}
			break;
		}
		if(!TRABAJO) continue;
		if(LibroA >= MAXL || LibroB >= MAXL) continue;
		vector < pair<int, int> > ans = ConsultaPalabra(LibroA, LibroB);
		for(auto i : ans){
			int* num = new int[4];
			num[0] = RESULTADO;
			num[1] = i.first;
			num[2] = i.second;
			num[3] = LibroA * MAXL + LibroB;
			cout << num[1] << " " << num[2] << endl;
			for(auto j : IPS){
				sprintf(auxIP, "%s", j.c_str());
				PaqueteDatagrama paks((char *) num, 16, auxIP, PUERTO);
				sock.envia(paks);
			}

			PaqueteDatagrama paks2((char *) num, 16, clienteIP, clientePuerto);
			sock.envia(paks2);
		}
		TRABAJO = 0;
	}
}

void InstruccionesMaestro(int t, char* IP){
	if(t == 0){
		if(AA + 1 >= MAXL){
			return;
		} 
		int* num = new int[4];
		num[0] = PETICION;
		num[1] = 0;
		
		num[2] = AA;
		num[3] = BB;
		sprintf(auxIP, "%s", IP);
		PaqueteDatagrama paks((char *) num, 16, auxIP, PUERTO);
		sock.envia(paks);
		BB++;
		if(BB == MAXL){
			AA++;
			BB = AA + 1;
		}
		
		
	}
}




int cont;

void* RecibePaquetes(void*){
	while(1){
		PaqueteDatagrama aux(16);
		sock.recibe(aux);
		int *datos =(int *) aux.obtieneDatos();
		//cout << datos[0] << " " << datos[1] << " " << datos[2] << " " << datos[3] << endl; 
		if(datos[0] == PETICION){
			pos = datos[1];
			LibroA = datos[2];
			LibroB = datos[3];
			TRABAJO = 1;
			cout << "Peticion :: " << LibroA << " " << LibroB << endl;
		}

		if(datos[0] == LIBRE){
			int* num = new int[4];
			num[0] = MAESTRO;
			num[1] = TRABAJO;
			PaqueteDatagrama paks((char *) num, 16, aux.obtieneDireccion(), aux.obtienePuerto());
			sock.envia(paks);
		}

		if(datos[0] == RESULTADO){
			GuardarRespuestas(make_pair(datos[1], datos[2]), datos[3]);
			res.insert(datos[3]);
			
		}

		if(datos[0] == MAESTRO){

			InstruccionesMaestro(datos[1], aux.obtieneDireccion());
		}

		if(datos[0] == CLIENTE){
			AA = datos[1];
			BB = datos[2];
			sprintf(clienteIP, "%s\n", aux.obtieneDireccion());;
			clientePuerto = aux.obtienePuerto();
			cout << "Checando " << clienteIP << " con " << clientePuerto << endl;
		}


   		
	}
}


void PrecalculaIPS(){
	IPS.push_back("192.168.0.139");
	IPS.push_back("192.168.0.119");
	IPS.push_back("192.168.0.120");
	IPS.push_back("192.168.0.128");
}



int main(){
	PrecalculaIPS();
	GeneraNombresLibros();
	for(int i = 0; i < MAXL; i++)
		AgregaPalabras(libros[i], i, infLibros[i]);
	//ImprimeRespuesta(ConsultaPalabra(0, 1), "A.txt", "B.txt", 0);
	
	pthread_t th1, th2, th3;
	pthread_create(&th1, NULL, &Trabajo, NULL);
	pthread_create(&th2, NULL, &Maestro, NULL);
	pthread_create(&th3, NULL, &RecibePaquetes, NULL);

	// Esperar a que los hilos terminen
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);

	return 0;
}