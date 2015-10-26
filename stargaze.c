#include "sidereal.c"
#include <math.h>
#include <stdlib.h>

// MATH

#define D2R 0.01745329251994 // degrees to radians

float* float9ToFloat16(float *a){
	float *m = malloc(sizeof(float)*16);
	m[0] = a[0];	m[1] = a[1];	m[2] = a[2];	m[3] = 0.0f;
	m[4] = a[3];	m[5] = a[4];	m[6] = a[5];	m[7] = 0.0f;
	m[8] = a[6];	m[9] = a[7];	m[10] = a[8];	m[11] = 0.0f;
	m[12] = 0.0f;	m[13] = 0.0f;	m[14] = 0.0f;	m[15] = 1.0f;
	return m;
}

// OPEN FRAMEWORKS
// Multiply a 3x3 matrix with a 3x3 matrix
float* mat3x3Mult(const float* A, const float* B) {
	float *C = malloc(sizeof(float)*9);
	C[0] = A[0] * B[0] + A[1] * B[3] + A[2] * B[6];
	C[1] = A[0] * B[1] + A[1] * B[4] + A[2] * B[7];
	C[2] = A[0] * B[2] + A[1] * B[5] + A[2] * B[8];
	C[3] = A[3] * B[0] + A[4] * B[3] + A[5] * B[6];
	C[4] = A[3] * B[1] + A[4] * B[4] + A[5] * B[7];
	C[5] = A[3] * B[2] + A[4] * B[5] + A[5] * B[8];
	C[6] = A[6] * B[0] + A[7] * B[3] + A[8] * B[6];
	C[7] = A[6] * B[1] + A[7] * B[4] + A[8] * B[7];
	C[8] = A[6] * B[2] + A[7] * B[5] + A[8] * B[8];
	return C;
}

void rotation(float degrees, float x, float y, float z){

}

float axialTiltAngle(int month, int day, int hour, int second){
	return 0;
}

float earthRotation(){
	float sidereal = 0.0;
	rotation(sidereal, 0, 0, 1);
	rotation(23.4, 1, 0 ,0);
	return 0.0f;
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

// GLKMatrix4MakeRotation((latitude)*DEG_TO_RAD, 0, 1, 0);   // latitude
// GLKMatrix4Rotate(matrix, longitude*DEG_TO_RAD, 0, 0, 1);  // longitude
float* latitudeLongitudeDisplacement(float latitude, float longitude){
	float *m = malloc(sizeof(float) * 9 );
	m[0] = cosf(latitude*D2R)*cosf(longitude*D2R);      m[1] = sinf(longitude*D2R);     m[2] = -sinf(latitude*D2R)*cosf(longitude*D2R);
	m[3] = cosf(latitude*D2R)*-sinf(longitude*D2R);     m[4] = cosf(longitude*D2R);     m[5] = -sinf(latitude*D2R)*-sinf(longitude*D2R);
	m[6] = sinf(latitude*D2R);                          m[7] = 0.0f;                    m[8] = cosf(latitude*D2R);
	return m;
}


void horizonalOrientation(float longitude, float latitude){

}

// your displacement from 0°N, 0°E, in the Gulf of Guinea off the coast of Africa, expressed a Rotation matrix.
float* celestialOrientation(float longitude, float latitude, int year, int month, int day, int hour, int minute, int second){
	float axT = 23.4;

	double J2000 = J2000DaysFromUTCNow();
	// double sidereal = greenwichMeanSiderealTime(J2000);
	double sidereal = localMeanSiderealTime(J2000, -97.73);

	float *r = malloc(sizeof(float) * 9);
	return r;
}
