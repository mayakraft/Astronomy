#include "sidereal.c"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
	int year, month, day, hour, minute, second;
	getTime(&year, &month, &day, &hour, &minute, &second);

	double J2000, sidereal, apparent;

	// sidereal at 0deg longitude
	J2000 = J2000DaysFromUTCNow();	
	sidereal = greenwichMeanSiderealTime(J2000);
	apparent = apparentSiderealTime(J2000);
	printf("\nGMT now: (%d/%d/%d %d:%2d:%2d)\n -    J2000: %f\n - SIDEREAL: %f\n - APPARENT: %f\n", year, month, day, hour, minute, second, J2000, sidereal, apparent);

	// sidereal at -74deg longitude, New York, NY, USA
	J2000 = J2000DaysFromUTCNow();	
	sidereal = localMeanSiderealTime(J2000, -74.00);
	apparent = apparentSiderealTime(J2000);
	printf("\nNYC now: (%d/%d/%d %d:%2d:%2d)\n -    J2000: %f\n - SIDEREAL: %f\n - APPARENT: %f\n", year, month, day, hour, minute, second, J2000, sidereal, apparent);

	year = 1994;
	month = 06; // June
	day = 16;   // 16th
	hour = 18;  //
	minute = 0; // 18:00
	second = 0; //

	J2000 = J2000DaysFromUTCTime(year, month, day, hour, minute, second);
	sidereal = greenwichMeanSiderealTime(J2000);
	apparent = apparentSiderealTime(J2000);
	printf("\nGMT historical: (%d/%d/%d %d:%2d:%2d)\n -    J2000: %f\n - SIDEREAL: %f\n - APPARENT: %f\n", year, month, day, hour, minute, second, J2000, sidereal, apparent);

/*
	for(int i = 0; i < 24; i++){
		month = 3;  // March
		day = 05;   // 5th
		hour = i;
		double J2000 = J2000DaysFromUTCTime(2015, month, day, hour, 0, 0);
		double sidereal = greenwichMeanSiderealTime(J2000);
		double apparent = apparentSiderealTime(J2000);
		printf("(2015/%d/%d %d:00)\t(%f)\t%f, %f\n",month, day, hour, J2000, sidereal, apparent);
	}

	printf("\n\n\n");

	for(int i = 0; i < 30; i++){
		month = 2;
		day = i;
		hour = 0;
		double J2000 = J2000DaysFromUTCTime(2015, month, day, hour, 0, 0);
		double sidereal = greenwichMeanSiderealTime(J2000);
		double apparent = apparentSiderealTime(J2000);
		printf("(2015/%d/%d %d:00)\t(%f)\t%f, %f\n",month, day, hour, J2000, sidereal, apparent);
	}
	printf("\n\n\n");

	for(int i = 0; i < 12; i++){
		month = i;
		day = 21;
		hour = 0;
		double J2000 = J2000DaysFromUTCTime(2015, month, day, hour, 0, 0);
		double sidereal = greenwichMeanSiderealTime(J2000);
		double apparent = apparentSiderealTime(J2000);
		printf("(2015/%d/%d %d:00)\t(%f)\t%f, %f\n",month, day, hour, J2000, sidereal, apparent);
	}

	printf("\n\n\n");

	minute = 50;
	for(int i = 0; i < 10; i++){
		month = 3;//rand()%12;
		day = i+1;//rand()%28;
		hour = 12;//rand()%24;
		minute -= 4;
		double J2000 = J2000DaysFromUTCTime(2015, month, day, hour, minute, 0);
		double sidereal = greenwichMeanSiderealTime(J2000);
		double apparent = apparentSiderealTime(J2000);
		printf("(2015/%d/%d %d:%d)\t(%f)\t%f, %f\n",month, day, hour, minute, J2000, sidereal, apparent);
	}
*/
	return 0;
}

