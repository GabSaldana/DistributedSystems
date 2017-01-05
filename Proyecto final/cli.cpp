#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdlib.h>
//g++ cli.cpp -o cli -std=c++11 

using namespace std;
const int MAXIMUN = 3;

//Vector con los nombres de los libros
vector <string> nameBooks;
//Libros vectorizados
vector <int> books[MAXIMUN];
//Vector con las respuestas de las substrings
vector <string> infBooks[MAXIMUN];
//vector que contiene los nuemros
unordered_map<string, int> hasheo;
//Vector con 
vector <pair <int, int> > respBook[MAXIMUN * MAXIMUN];
int lastvalue;

class Token{
	public:
		string value;
    private:
        friend ostream& operator<<(ostream&,Token const&);
        friend istream& operator>>(istream&,Token&);
        
};

//OBTENEMOS TODAS LAS PALABRAS
istream& operator>>(istream& str,Token& data){
    if (!str){   
    	return str;
    }

    char x;
    do{
        x = str.get();
    }
    while(str && isspace(x) && (x != '\n'));

    if (!str){
        return str;
    }
    data.value  ="";

    if (x == '\n'){ 
    	data.value  = "";
        return str;
    }

    str.unget();
    str >> data.value;

    return str;
}

void Print(vector < pair <int, int> > x, int A, int B){
	cout << "\n\nCadena(s) entre  " << nameBooks[A] << " y " << nameBooks[B] << " con tokens (" << x.size() << "):" << endl;
	for(int i = 1; i <= x.size(); i++){
		cout << "CADENA " << i << ": <";
		for(int j = x[i - 1].first; j <= x[i - 1].second; j++){
			cout << infBooks[A][j] << " ";
		}
		cout << ">\n";
	}
}

//INSERTAMOS CADA UNO DE LOS NOMBRES DE LOS TEXOS A SER UTILIZADOS
void NameBooks(){
	string nombre;

	nombre = "Bestiario-Julio_Cortazar.txt";//0
	nameBooks.push_back(nombre);
	nombre = "Demian-Hermann_Hesse.txt";//1
	nameBooks.push_back(nombre);
	nombre = "Dioses_Y_Heroes_De_La_Antigua_Grecia-Robert_Graves.txt";//2
	nameBooks.push_back(nombre);
	nombre = "El_Amante-Marguerite_Duras.txt";//3
	nameBooks.push_back(nombre);
	nombre = "El_hombre_en_busca_de_sentido-Viktor_Frankl.txt";//4
	nameBooks.push_back(nombre);
	nombre = "Territorio_comanche-Arturo_Perez_Reverte.txt";//5
	nameBooks.push_back(nombre);
	nombre = "Una_mujer_endemoniada-Jim_Thompson.txt";//6
	nameBooks.push_back(nombre);
	nombre = "Una_navidad_diferente-John_Grisham.txt";//7
	nameBooks.push_back(nombre);
	nombre = "A.txt";//8
	nameBooks.push_back(nombre);
	nombre = "B.txt";//9
	nameBooks.push_back(nombre);

}


void AddWords(vector<int>& palabras, int pos, vector <string>& info){
	ifstream   f(nameBooks[pos]);
	Token x;
	while(f >> x){//lectura de el archivo
		string aux = x.value;
		if(aux.size() == 0) continue;
		info.push_back(aux);
		if(hasheo.find(aux) == hasheo.end())//Palabras convertidas a numeros
			hasheo[aux] = ++lastvalue;

		palabras.push_back(hasheo[aux]); 
    }
}

void BestAnswer(pair <int, int> x, vector <pair <int, int> >& respuestas, int& maxTam){
	if(maxTam < x.second - x.first + 1){
		respuestas.clear();
		respuestas.push_back(x);
		maxTam = x.second - x.first + 1;
	}else if(maxTam == x.second - x.first + 1){
		respuestas.push_back(x);
	}
}

vector< pair<int, int> > CheckWord(int A, int B){
	vector < pair <int, int> > respuestas;
	int N = books[A].size();
	int M = books[B].size();

	int maxTam = -1;
	
	for(int x = 0; x < N; x++){

		int maxAns = 0;
		for(int i = 0; i < M; i++){
			int tam = 0;
			while(x + tam < N && tam + i < M && books[A][x + tam] == books[B][i + tam])
				tam++;
			if(maxAns < tam){
				maxAns = tam;
				BestAnswer(make_pair(x, x + maxAns - 1), respuestas, maxTam);
			}
		}
	}
	return respuestas;
}


int main(int args, char *argv[]) {

	NameBooks();
	for(int i = 0; i < MAXIMUN; i++)
		AddWords(books[i], i, infBooks[i]);
	// 0 y 1  2 y 3  1y 3
	Print(CheckWord(0, 2), 7, 4);//no de cadenas que queremos mostrar y los indices de los libros
	
	return 0;
}
