// convert dates into J2000 format
//
// units are in days
//   (+ one day) is (+ 1.0)
// 0.0 in J2000 is January 1st, 2000
//
// robby kraft, mit open source software license

#include <time.h>
#include <math.h>

double mod360(double input){
	if(input > 360.0){
		int n = input / 360.0;
		return input - n*360;
	}
	if(input < 0.0){
		int n = input / 360.0;
		return input - (n-1)*360;
	}
	return input;
}

// date input is human-readable: month and day are one-based indexing (March 1st is 03,01)
void getTime(int *year, int *month, int *day, int *hour, int *minute, int *second){
	time_t current;
	time(&current);
	struct tm GMT;
	GMT = *gmtime(&current);
	*year = GMT.tm_year + 1900; /* The number of years since 1900   */
	*month = GMT.tm_mon + 1;    /* month, range 0 to 11             */
	*day = GMT.tm_mday;         /* day of the month, range 1 to 31  */
	*hour = GMT.tm_hour;        /* hours, range 0 to 23             */
	*minute = GMT.tm_min;       /* minutes, range 0 to 59           */
	*second = GMT.tm_sec;       /* seconds,  range 0 to 59          */
	// int tm_isdst;       /* daylight saving time             */
}

double J2000SecondsFromJ2000Days(double J2000Days){
	return J2000Days * 60 * 60 * 24;
}
double J2000CenturiesFromJ2000Days(double J2000Days){
	return J2000Days / 36525.0;
}

// time since january 1st, at 12:00 (noon)
double J2000DaysFromUTCNow(){
	int year, month, day, hour, minute, second;
	getTime(&year, &month, &day, &hour, &minute, &second);
	double wholePart = 367*year-floor(7*(year+floor((month+9)/12.0))/4.0)+floor(275*month/9.0)+day-730531.5;
	double fractionalPart = (hour + minute/60.0 + second/3600.0)/24.0;
	// return value units in days
	return (double)wholePart + fractionalPart;
}
double J2000SecondsFromUTCNow(){
	return J2000SecondsFromJ2000Days(J2000DaysFromUTCNow());
}
double J2000CenturiesFromUTCNow(){
	return J2000CenturiesFromJ2000Days(J2000DaysFromUTCNow());
}

// time since january 1st, at 12:00 (noon)
// date input is human-readable: month and day are one-based indexing (March 1st is 03,01)
double J2000DaysFromUTCTime(int year, int month, int day, int hour, int minute, int second){
	double wholePart = 367*year-floor(7*(year+floor((month+9)/12.0))/4.0)+floor(275*month/9.0)+day-730531.5;
	double fractionalPart = (hour + minute/60.0 + second/3600.0)/24.0;
	// return value units in days
	return (double)wholePart + fractionalPart;
}
double J2000SecondsFromUTCTime(int year, int month, int day, int hour, int minute, int second){
	return J2000SecondsFromJ2000Days(J2000DaysFromUTCTime(year, month, day, hour, minute, second));
}
double J2000CenturiesFromUTCTime(int year, int month, int day, int hour, int minute, int second){
	return J2000CenturiesFromJ2000Days(J2000DaysFromUTCTime(year, month, day, hour, minute, second));
}// time since january 1st, at 12:00 (noon)
// date input is human-readable: month and day are one-based indexing (March 1st is 03,01)
void UTCTimeFromJ2000Days(double J2000){//, int *year, int *month, int *day, int *hour, int *minute, int *second){
	double fractionalPart = fmod(J2000, 1);
	int wholePart = J2000 - fractionalPart;
	printf("%d  %f\n", wholePart, fractionalPart);	

	// double J2000 = 367 * year 
	//                - floor(7 * (year+floor((month+9)/12.0) ) / 4.0) 
	//                + floor(275 * month / 9.0)
	//                + day
	//                - 730531.5
	//                + (hour + minute/60.0 + second/3600.0) / 24.0


	// double J2000 - floor(275 * month / 9.0) - day + 730531.5 - (hour + minute/60.0 + second/3600.0) / 24.0
	//              = 367 * yea - 7 / 4.0 * (year+floor((month+9)/12.0) )  
	               

	// double fractionalPart = (hour + minute/60.0 + second/3600.0)/24.0;

	// return value units in days
	// *year = GMT.tm_year + 1900; /* The number of years since 1900   */
	// *month = GMT.tm_mon + 1;    /* month, range 0 to 11             */
	// *day = GMT.tm_mday;         /* day of the month, range 1 to 31  */
	// *hour = GMT.tm_hour;        /* hours, range 0 to 23             */
	// *minute = GMT.tm_min;       /* minutes, range 0 to 59           */
	// *second = GMT.tm_sec;       /* seconds,  range 0 to 59          */

	double year = 2000 + (J2000-2000)/365.25;

	printf("\nYear:%f\n",year);

}

// double daysSinceJ2000(int timeZone, int year, int month, int day, int hour, int minute, int second){
// 	return UTCDaysSinceJ2000(year, month, day, hour + timeZone, minute, second);
// }
