#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


int main(int argc, char const *argv[])
{
	double s=0;
	double c=0;
	double t=0;
	double l=0;
	double sq=0;

	double i=0;
	double long x=10000000;
	while(i<x){
		s+=sin(i);
		c+=cos(i);
		t+=tan(i);
		l+=log(i);
		sq+=sqrt(i);
		i++;
	}
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(8);
	cout<<s<<endl;
	cout<<c<<endl;
	cout<<t<<endl;
	cout<<l<<endl;
	cout<<sq<<endl;

	return 0;
}