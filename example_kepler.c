// the format of this number is: centuries after the year 2000
//double time = -.17;//.138767; // mid November 2013
// double t = -499384800.000000 / 60.0 / 60.0 / 24.0 / 365.0 / 100.0;  // March 5 1984
double day_unit = 1.0 / 365.25 / 100.0;

// time = (year-2000)/100 + day_of_the_year/36525
// where day_of_the_year would be 42 for February 11th.

#include "kepler.c"
#include <stdio.h>

#include "J2000.c"

int main(){

	double x, y, z;

	double J2000days = J2000DaysFromUTCTime(1984, 3, 05, 8, 0, 0);
	double J2000centuries = J2000days / 365.25 / 100.0;

	printf("TIME: %f\n", J2000centuries);
	
	printf("time,x,y,z\n");
	for(float i = 0; i < 365.25*2; i+=30.4375){
		calculateLocationOfPlanet(2, J2000centuries + day_unit * i, &x, &y, &z);
		printf("%f,%f,%f,%f\n", J2000centuries + day_unit * i, x, y, z);
		// printf("%f: %f\t%f\t%f\n", J2000centuries + day_unit * i, x, y, z);
	}

	return 0;
}