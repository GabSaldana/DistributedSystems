#include <bits/stdc++.h>
#include "SocketDatagrama.h"

using namespace std;


const int MAXL = 3;


vector <string> nombreLibros;
vector <int> libros[MAXL];
vector <string> infLibros[MAXL];
unordered_map<string, int> hasheo;
vector <pair <int, int> > respuestasLibro[MAXL * MAXL];
int lastvalue;
set <int> res;

SocketDatagrama sock(4000);

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

void GeneraNombresLibros(){
	string nombre;

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


void* RecibePaquetes(void*){
	while(1){
		PaqueteDatagrama aux(16);
		sock.recibe(aux);
		int *datos =(int *) aux.obtieneDatos();
		cout << datos[0] << " " << datos[1] << " " << datos[2] << " " << datos[3] << endl; 
		
		if(datos[0] == 3){
			GuardarRespuestas(make_pair(datos[1], datos[2]), datos[3]);
			res.insert(datos[3]);
			if(res.size() == (MAXL * (MAXL - 1)) / 2){
				sleep(3);
				for(int i = 0; i < MAXL; i++){
					for(int j = i + 1; j < MAXL; j++){
						ImprimeRespuesta(respuestasLibro[i * MAXL + j], i, j);
					}
				}
				break;
			}
		}

	}
}



int main(int args, char *argv[]) {

	GeneraNombresLibros();
	for(int i = 0; i < MAXL; i++)
		AgregaPalabras(libros[i], i, infLibros[i]);
	int A = atoi(argv[2]);
	int B = atoi(argv[3]);
	char* ip = argv[1];
	int* num = new int[4];
	num[0] = 5;
	num[1] = A;
	num[2] = B;
	PaqueteDatagrama data((char*) num, 16, ip, 8200);
	
	sock.envia(data);
	pthread_t th1;
	pthread_create(&th1, NULL, &RecibePaquetes, NULL);
	pthread_join(th1, NULL);
	return 0;
}
