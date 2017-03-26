#include "J2000.h"
#include "sidereal.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// DEFS
#define D2R 0.01745329251994    // degrees to radians
#define R2D 57.295779513082321  // radians to degrees
#define EARTH_AX_DEG 23.446236  // Earth's axial tilt, in degrees
// MATH
#ifndef LINEAR_ALGEBRA_MATH
#define LINEAR_ALGEBRA_MATH
// Rotate X
void makeMat3XRot(float *m, float angle){
	m[0] = 1;   m[1] = 0;           m[2] = 0;
	m[3] = 0;   m[4] = cos(angle);  m[5] = -sin(angle);
	m[6] = 0;   m[7] = sin(angle);  m[8] = cos(angle);
}
// Rotate Y
void makeMat3YRot(float *m, float angle){
	m[0] = cos(angle);  m[1] = 0;   m[2] = -sin(angle);
	m[3] = 0;           m[4] = 1;   m[5] = 0;
	m[6] = sin(angle);  m[7] = 0;   m[8] = cos(angle);
}
// Rotate Z
void makeMat3ZRot(float *m, float angle){
	m[0] = cos(angle);  m[1] = -sin(angle); m[2] = 0;
	m[3] = sin(angle);  m[4] = cos(angle);  m[5] = 0;
	m[6] = 0;           m[7] = 0;           m[8] = 1;
}
void mat3ToMat4(float *in, float *result){
	result[0] = in[0];  result[1] = in[1];  result[2] = in[2];  result[3] = 0.0f;
	result[4] = in[3];  result[5] = in[4];  result[6] = in[5];  result[7] = 0.0f;
	result[8] = in[6];  result[9] = in[7];  result[10] = in[8]; result[11] = 0.0f;
	result[12] = 0.0f;  result[13] = 0.0f;  result[14] = 0.0f;  result[15] = 1.0f;
}
// multiply two 3x3 matrices, a and b, store result into c
void mat3x3Mult(const float* a, const float* b, float* c) {
	c[0] = a[0] * b[0] + a[1] * b[3] + a[2] * b[6];
	c[1] = a[0] * b[1] + a[1] * b[4] + a[2] * b[7];
	c[2] = a[0] * b[2] + a[1] * b[5] + a[2] * b[8];
	c[3] = a[3] * b[0] + a[4] * b[3] + a[5] * b[6];
	c[4] = a[3] * b[1] + a[4] * b[4] + a[5] * b[7];
	c[5] = a[3] * b[2] + a[4] * b[5] + a[5] * b[8];
	c[6] = a[6] * b[0] + a[7] * b[3] + a[8] * b[6];
	c[7] = a[6] * b[1] + a[7] * b[4] + a[8] * b[7];
	c[8] = a[6] * b[2] + a[7] * b[5] + a[8] * b[8];
}
// multiply one 3x3 matrices with one 3x vector, result is a 3x vector
void mat3Vec3Mult(const float m[9], const float v[3], float result[3]){
	result[0] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2];
	result[1] = m[3] * v[0] + m[4] * v[1] + m[5] * v[2];
	result[2] = m[6] * v[0] + m[7] * v[1] + m[8] * v[2];
}
void printfVec3(float *v){ printf("(%f)\n(%f)\n(%f)\n", v[0], v[1], v[2]); }
void printfMat3(float *m){ printf("[%f %f %f]\n[%f %f %f]\n[%f %f %f]\n", m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]); }
void printfMat4(float *m){ printf("[%f %f %f %f]\n[%f %f %f %f]\n[%f %f %f %f]\n[%f %f %f %f]\n", m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9], m[10], m[1], m[12], m[13], m[14], m[15]); }

#endif

///////////////////////////////////////////////////////////////
// source = Practical Astronomy with your Calculator
//          by Peter Duffett-Smith

// Matrix C, in the book
void generateAxialTiltMatrix(float* result){
// for multiplying against declination and right ascention coordinates
// and getting ecliptic latitude and longitude coordinates
	// Earth's axial tilt
	float angle = EARTH_AX_DEG * D2R;
	result[0] = 1;   result[1] = 0;           result[2] = 0;
	result[3] = 0;   result[4] = cos(angle);  result[5] = sin(angle);
	result[6] = 0;   result[7] = -sin(angle); result[8] = cos(angle);
}
// Matrix C', in the book
void generateAxialTiltMatrixPrime(float* result){
// for multiplying against ecliptic latitude and longitude coordinates
// and getting declination and right ascention coordinates
	// Earth's axial tilt
	float angle = EARTH_AX_DEG * D2R;
	result[0] = 1;   result[1] = 0;           result[2] = 0;
	result[3] = 0;   result[4] = cos(angle);  result[5] = -sin(angle);
	result[6] = 0;   result[7] = sin(angle);  result[8] = cos(angle);
}

// Matrix B, in the book
void generateSiderealTimeMatrix(float *result, float localSiderealTime){
// for multiplying against one and getting the other. works either way.
// (a): altitude and declination
// (b): hour angle and declination
	// localSiderealTime must be in degrees, 0deg to 360deg
	// if it's in hours: multiply by 15. example: 18hrs * 15 = 270deg
	float angle = localSiderealTime * D2R; // convert to radians
	result[0] = cos(angle);  result[1] = sin(angle);   result[2] = 0;
	result[3] = sin(angle);  result[4] = -cos(angle);  result[5] = 0;
	result[6] = 0;           result[7] = 0;            result[8] = 1;
}

// Matrix A, in the book
void generateGeographicLatitudeMatrix(float *result, float latitude){
// for multiplying against one and getting the other. works either way.
// (a): azimuth and altitude
// (b): hour angle and declination
	float radians = latitude * D2R;
	result[0] = -sin(radians); result[1] = 0;   result[2] = cos(radians);
	result[3] = 0;             result[4] = -1;  result[5] = 0;
	result[6] = cos(radians);  result[7] = 0;   result[8] = sin(radians);
}

void generateColumnVector(float a, float b, float *result){
	result[0] = cos(a) * cos(b);
	result[1] = sin(a) * cos(b);
	result[2] = sin(b);
}

void extractCoordinatesFromColumnVector(const float v[3], float *a, float *b){
	*a = atan2(v[1], v[0]);
	*b = asin(v[2]);
}

///////////////////////////////////////////////////////////////
// Generalized functions

void eclipticToHorizontal(float eclipticLat, float eclipticLon, float observerLat, float sidereal, float *azimuth, float *altitude){
	// last 2 arguments are the result: azimuth and altitude

	// generate 3 orientation matrices
	float m1[9], m2[9], m3[9];
	generateGeographicLatitudeMatrix(m1, observerLat);
	generateSiderealTimeMatrix(m2, sidereal);
	generateAxialTiltMatrixPrime(m3);
	// multiply 3 matrices together
	float mmult1[9], mmult2[9];
	mat3x3Mult(m2, m3, mmult1);
	mat3x3Mult(m1, mmult1, mmult2);
	// multiply input by orientation matrix
	float v[3], answer[3];
	generateColumnVector(eclipticLat * D2R, eclipticLon * D2R, v);
	mat3Vec3Mult(mmult2, v, answer);
	extractCoordinatesFromColumnVector(answer, azimuth, altitude);
	*azimuth *= R2D;
	*altitude *= R2D;

	// if(0){
	// 	printf("\nGeographic Latitude Matrix (latitude: %f):\n",observerLat);
	// 	printfMat3(m1);
	// 	printf("\nSidereal Time Matrix (sidereal: %f):\n",sidereal);
	// 	printfMat3(m2);
	// 	printf("\nAxial Tilt Matrix:\n");
	// 	printfMat3(m3);
	// 	printf("\nProduct of first 2 Matrices:\n");
	// 	printfMat3(mmult1);
	// 	printf("\nProduct of all 3 Matrices:\n");
	// 	printfMat3(mmult2);
	// 	printf("\nColumn Vector:\n");
	// 	printfVec3(v);
	// 	printf("\nFinal Vector:\n");
	// 	printfVec3(answer);
	// 	printf("\nFinal Answer:\nAzimuth: %f\nAltitude: %f\n", *azimuth, *altitude);		
	// }
}

void eclipticToHorizontalWithDate(float eclipticLat, float eclipticLon, float observerLat, float observerLon, int year, int month, int day, int hour, int minute, int second, float *azimuth, float *altitude){
	// last 2 arguments are the result: azimuth and altitude
	double J2000 = J2000DaysFromUTCTime(year, month, day, hour, minute, second);
	double sidereal = localMeanSiderealTime(J2000, observerLon);
	eclipticToHorizontal(eclipticLon, eclipticLat, observerLat, sidereal, azimuth, altitude);
}

//90 degree rotation around Y (second axis)
//180 degree rotation around Z (third axis)
float phoneToHorizonal3x3[9] = {
	0.0f, 0.0f, 1.0f,
	0.0f, -1.0f, 0.0f,
	1.0f, 0.0f, 0.0f };

float phoneToHorizonal4x4[16] = {
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,1.0f, 
};
