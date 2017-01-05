#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


int main(int argc, char const *argv[])
{
	//int n=4294967295;
	int n=1757600;
	//int n=500000;
	srand(time(0));
	char A;
	char msg[n];
	int i=0;
	while(i<n){
		for (int x = 0; x < 3; x++)
		{
			A= 65+(rand()%26); 
			msg[i]=A;
			i++;
		}
		msg[i]=' ';
		i++;


	}
	msg[n]='\0';
	i=0;
	int cont=0;
	while(i<n){
		if(msg[i]=='I')
			if(msg[i+1]=='P')
				if(msg[i+2]=='N')
					cont++;
		i+=4;
	}

	//cout<<msg<<endl;
	cout<<" \nContador"<<cont<<endl;
	return 0;
}