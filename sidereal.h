// Sidereal Time
// 
// robby kraft
// mit open source software license

#import <math.h>

// date units in J2000 days. see:J2000.h
double greenwichMeanSiderealTime(double J2000Day){
	// In 10 years, the approximation error will be 0.001 seconds. 30
	// years from now the error will still be better than 0.01 seconds.
	// A century from now, the approximation error will be 0.1 seconds.
	// However, 10 centuries from now the error will be 10 seconds....

	// longer time reach, or set to 0 for quick calculation
	// double LTR = 0.0;
	double LTR = 0.000388 * pow(J2000Day/36525.0, 2);
	// Errors through truncation with longer time reach amount to 0.008
	// seconds 1000 years into the future or past, and 0.0003 seconds
	// 300 years into the future or past. With this kind of calculation,
	// you must be very careful about time. The formulas here use UT,
	// not dynamical time, known as TDT. Formulas used to predict the
	// positions of planets, the Moon, eclipses and so on use TDT. 

// precision to about 5 decimal places: error 0.000001
	return mod360(280.46061837 + 360.98564736629 * J2000Day + LTR);
}

// J2000 time must be from GMT time zone
double localMeanSiderealTime(double J2000Day, double longitude){
	double LTR = 0.000388 * pow(J2000Day/36525.0, 2);
	return mod360(280.46061837 + 360.98564736629 * J2000Day + LTR + longitude);
}

// incorporates the wobble caused by the moon's pull, the barycenter is not at the center of the Earth
double apparentSiderealTime(double J2000Day){
	// format time
	double t = J2000Day / 36525.0;
	// GMST = greenwichMeanSiderealTime();
	// constants
	double Om = mod360(125.04452 - 1934.136261 * t);
	double L = mod360(280.4665 + 36000.7698 * t);
	double L1 = mod360(218.3165 + 481267.8813 * t);
	double e = mod360(23.439 - 0.0000004 * t);
	// calculations
	double dp = -17.2*sin(Om) -1.32*sin(2*L) -0.23*sin(2*L1) +0.21*sin(2*Om);
	double de =   9.2*cos(Om) +0.57*cos(2*L) + 0.1*cos(2*L1) -0.09 *cos(2*Om);
	// e = eps + de;
	e = dp + de;
	// double correction = dp * cos(e) / 15;
	double correction = dp * cos(e) / 3600.0;
	return correction;
}