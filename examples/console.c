#include <stdio.h>

#include "../J2000.h"
#include "../sidereal.h"
#include "../kepler.h"
#include "../stargaze.h"

int main(){

	int year, month, day, hour, minute, second, longitude;
	double x, y, z, sidereal, apparent, J2000days, J2000seconds, J2000centuries;
	char *planetNames[9] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};
	char *monthNames[13] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

printf("\n╔══════════════════════════════════╗");
printf("\n║             KEPLER.H             ║");
printf("\n╚══════════════════════════════════╝\n");

	// get now time
	getTime(&year, &month, &day, &hour, &minute, &second);

	// location today
	J2000centuries = J2000CenturiesFromUTCTime(year, month, day, hour, minute, second);
	printf("\nPlanetary positions: (%s %d %d %d:%02d:%02d)\n", monthNames[month], day, year, hour, minute, second);
	for(int i = 0; i < 9; i++){
		calculateLocationOfPlanet(i, J2000centuries, &x, &y, &z);
		printf("%s\t%d°\t(x:%.3f  y:%.3f  z:%.3f)\n", planetNames[i], (int)(atan2(y,x)/M_PI*180), x, y, z );
	}

	// historical location
	year = 1984;  month = 3;  day = 5;  hour = 16;  minute = 0;  second = 0;
	J2000centuries = J2000CenturiesFromUTCTime(year, month, day, hour, minute, second);
	printf("\nPlanetary positions: (%s %d %d %d:%02d:%02d)\n", monthNames[month], day, year, hour, minute, second);
	for(int i = 0; i < 9; i++){
		calculateLocationOfPlanet(i, J2000centuries, &x, &y, &z);
		printf("%s\t%d°\t(x:%.3f  y:%.3f  z:%.3f)\n", planetNames[i], (int)(atan2(y,x)/M_PI*180), x, y, z );
	}

printf("\n╔══════════════════════════════════╗");
printf("\n║            SIDEREAL.H            ║");
printf("\n╚══════════════════════════════════╝\n");

	// get now time
	getTime(&year, &month, &day, &hour, &minute, &second);

	// convert time into J2000
	J2000centuries = J2000CenturiesFromUTCNow();
	J2000days = J2000DaysFromUTCNow();
	J2000seconds = J2000SecondsFromUTCNow();
	printf("\nNow: (%s %d %d %d:%02d:%02d)\n -J2000(cent): %f\n -J2000(day): %f\n -J2000(sec): %f\n", monthNames[month], day, year, hour, minute, second, J2000centuries, J2000days, J2000seconds);

	// sidereal at 0deg longitude	
	sidereal = greenwichMeanSiderealTime(J2000days);
	apparent = apparentSiderealTime(J2000days);
	printf("  GMT:\n   * SIDEREAL: %f\n   * APPARENT: %f\n", sidereal, apparent);
	// sidereal at -74deg longitude, New York, NY, USA
	sidereal = localMeanSiderealTime(J2000days, -74.00);
	apparent = apparentSiderealTime(J2000days);
	printf("  New York City:\n   * SIDEREAL: %f\n   * APPARENT: %f\n", sidereal, apparent);

	// historical date
	year = 1984;  month = 03;  day = 5;  hour = 16;  minute = 0;  second = 0;
	J2000centuries = J2000CenturiesFromUTCTime(year, month, day, hour, minute, second);
	J2000days = J2000DaysFromUTCTime(year, month, day, hour, minute, second);
	J2000seconds = J2000SecondsFromUTCTime(year, month, day, hour, minute, second);
	sidereal = greenwichMeanSiderealTime(J2000days);
	apparent = apparentSiderealTime(J2000days);
	printf("\nHistorical: (%s %d %d %d:%02d:%02d)\n -J2000(cent): %f\n -J2000(day): %f\n -J2000(sec): %f\n", monthNames[month], day, year, hour, minute, second, J2000centuries, J2000days, J2000seconds);
	printf("  GMT:\n   * SIDEREAL: %f\n   * APPARENT: %f\n", sidereal, apparent);


printf("\n╔══════════════════════════════════╗");
printf("\n║          ON PLANET EARTH         ║");
printf("\n╚══════════════════════════════════╝\n");

	int planet = 2;  // earth
	printf(" LONGITUDE             TIME               ORBIT          ROTATION\n");

		// year = 2016;
		// month = 12;
		// day = 21;
		// hour = 23;
		// minute = 56;
		// second = 5;

printf("\nchange in Longitude\n");
	for(int i = 180; i > -180; i-=10){
		longitude = i;
		year = 2016;
		month = 12;
		day = 21;
		hour = 16;
		minute = 8;
		second = 0;
		double J2000day = J2000DaysFromUTCTime(year, month, day, hour, minute, second);
		double sidereal = localMeanSiderealTime(J2000day, longitude);
		double apparent = apparentSiderealTime(J2000day);
		calculateLocationOfPlanet(planet, J2000CenturiesFromJ2000Days(J2000day), &x, &y, &z);
		printf("%s %4d° %9s %2d, %d (%2d:%02d)   %7.2f°   SIDE:%6.2f   APPR:%.5f\n", planetNames[planet], longitude, monthNames[month], day, year, hour, minute, (atan2(y,x)/M_PI*180), sidereal, apparent);
	}
printf("\nchange in hour\n");
	for(int i = 0; i < 24; i++){
		longitude = 0;
		year = 2016;
		month = 12;
		day = 21;
		hour = i;
		minute = 8;
		second = 0;
		double J2000day = J2000DaysFromUTCTime(year, month, day, hour, minute, second);
		double sidereal = greenwichMeanSiderealTime(J2000day);
		double apparent = apparentSiderealTime(J2000day);
		calculateLocationOfPlanet(planet, J2000CenturiesFromJ2000Days(J2000day), &x, &y, &z);
		printf("%s %4d° %9s %2d, %d (%2d:%02d)   %7.2f°   SIDE:%6.2f   APPR:%.5f\n", planetNames[planet], longitude, monthNames[month], day, year, hour, minute, (atan2(y,x)/M_PI*180), sidereal, apparent);
	}

printf("\nchange in day\n");
	for(int i = 0; i < 30; i++){
		longitude = 0;
		year = 2016;
		month = 12;
		day = i;
		hour = 16;
		minute = 8;
		second = 0;
		double J2000day = J2000DaysFromUTCTime(year, month, day, hour, minute, second);
		double sidereal = greenwichMeanSiderealTime(J2000day);
		double apparent = apparentSiderealTime(J2000day);
		calculateLocationOfPlanet(planet, J2000CenturiesFromJ2000Days(J2000day), &x, &y, &z);
		printf("%s %4d° %9s %2d, %d (%2d:%02d)   %7.2f°   SIDE:%6.2f   APPR:%.5f\n", planetNames[planet], longitude, monthNames[month], day, year, hour, minute, (atan2(y,x)/M_PI*180), sidereal, apparent);
	}

printf("\nchange in month\n");
	for(int i = 1; i < 13; i++){
		year = 2016;
		month = i;
		day = 21;
		hour = 16;
		minute = 8;
		second = 0;
		double J2000day = J2000DaysFromUTCTime(year, month, day, hour, minute, second);
		double sidereal = greenwichMeanSiderealTime(J2000day);
		double apparent = apparentSiderealTime(J2000day);
		calculateLocationOfPlanet(planet, J2000CenturiesFromJ2000Days(J2000day), &x, &y, &z);
		printf("%s %4d° %9s %2d, %d (%2d:%02d)   %7.2f°   SIDE:%6.2f   APPR:%.5f\n", planetNames[planet], longitude, monthNames[month], day, year, hour, minute, (atan2(y,x)/M_PI*180), sidereal, apparent);
	}

/*	for(int i = 0; i < 12; i++){
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


printf("\n╔══════════════════════════════════╗");
printf("\n║     CONVERT REFERENCE FRAMES     ║");
printf("\n╚══════════════════════════════════╝\n");

printf("\nExample 1 from Practical Astronomy with your Calculator:\n");

	// what are the Azimuth and Altitude of a planet whose ecliptic coordinates are
	// longitude: 97 deg 38 min 17.228 sec
	// latitude: -17 deg 51 min 28.688 sec
	// for an observer at geographic latitude: 52 deg 10 min 31.0 sec
	// at local sidereal time: 5h 9m 21.103s ?

	double observerLat = 52.175278;  // degrees
	double eclipticLat = 97.638119;  // degrees
	double eclipticLon = -17.857969; // degrees
	double siderealTime = 5.155862;  // hours
	double STDeg = siderealTime*15;  // degrees

	double siderealDeg = siderealTime * 15; // degrees

	float azimuth, altitude;

	// celestialOrientationWithDate(40, -97.73, 2016, 03, 05, 0, 0, 0);
	eclipticToHorizontal(eclipticLat, eclipticLon, observerLat, siderealDeg, &azimuth, &altitude);
	printf("What are the Azimuth and Altitude of a planet whose ecliptic coordinates are\nLat:%f deg\nLon:%f deg\n", eclipticLat, eclipticLon);
	printf("for an observer at geographic\nLat:%f deg\nSidereal Time:%f hrs\n", observerLat, siderealTime);
	printf("\nFinal Answer:\nAzimuth: %f\nAltitude: %f\n", azimuth, altitude);


	return 0;
}

/* the date is in J2000
 * the format of this number is: centuries after the year 2000
 * time = (year-2000)/100 + day_of_the_year/36525
 * where day_of_the_year would be 42 for February 11th.
*/