
#include <iostream>

using namespace std;

/*Se dice que un número M es un número de Mersenne
 si es una unidad menor que una potencia de 2.
 M n = 2 n − 1. {\displaystyle M_{n}=2^{n}-1.} M_n=2^n-1.*/
int main(){


	//primos
	//int n=4294967291;
	int n=2305843009213693951;
	//int n=1024;
	//no primo
	int i=2;
	bool flag=false;
	while(i < n){

		//cout << "i:" << i << endl;
		if((n % i == 0 )&& (i != 1)){

			break;
		}else{

			flag = true;
		}
		i++;
	}

	if(flag == true)
		cout << "Es primo" << endl;
	else
		cout << "No es primo" << endl;

	return 0;
}