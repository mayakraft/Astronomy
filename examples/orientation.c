#include "../lib/world.h"
#include "../stargaze.h"

void drawUnitGimbal(float red, float green, float blue);
void drawWorldAxes();

float orientationMatrix[16];
float axialTiltMatrix[9];
float geographicLatMatrix[9];

float observerLat = 18.45;  // degrees
float observerLon = -66.0;  // degrees
// double eclipticLat = 97.638119;  // degrees
// double eclipticLon = -17.857969; // degrees
// double siderealTime = 5.155862;  // hours
// double STDeg = siderealTime*15;  // degrees
// double siderealDeg = siderealTime * 15; // degrees
// eclipticToHorizontal(eclipticLat, eclipticLon, observerLat, siderealDeg, &azimuth, &altitude);

void setup(){
	emptyPerspective();
	GROUND = 0;
	GRID = 0;
	setMat4Identity(orientationMatrix);
	generateAxialTiltMatrixPrime(axialTiltMatrix);
}
void update(){
	if(keyboard[']']){
		observerLon += 0.5;
	} if(keyboard['[']){
		observerLon -= 0.5;
	}

	float siderealMatrix[9];
	double J2000 = J2000DaysFromUTCNow();
	double sidereal = localMeanSiderealTime(J2000, observerLon);
	generateSiderealTimeMatrix(siderealMatrix, sidereal);
	// multiply matrices together
	float matrixProduct[9];
	mat3x3Mult(siderealMatrix, axialTiltMatrix, matrixProduct);

	generateGeographicLatitudeMatrix(geographicLatMatrix, observerLat);
	// convert astronomy matrix to OpenGL matrix
	mat3ToMat4(siderealMatrix, orientationMatrix);
}

void draw3D(){
	// glPushMatrix();
		// glScalef(5.0, 5.0, 5.0);
	// glPopMatrix();

	glPushMatrix();
	float sp = 4;

// TOP ROW
		// glPushMatrix();
		// 	glTranslatef(-sp, sp, 0);
		// 	glRotatef(-lookOrientation[1], 1, 0, 0);
		// 	glRotatef(-lookOrientation[0], 0, 1, 0);
		// 	drawUnitGimbal(1.0, 1.0, 1.0);
		// glPopMatrix();

		// glPushMatrix();
		// 	glTranslatef(0, sp, 0);
		// 	glRotatef(-lookOrientation[1], 1, 0, 0);
		// 	glRotatef(-lookOrientation[0], 0, 1, 0);
		// 	drawUnitGimbal(1.0, 1.0, 1.0);
		// glPopMatrix();

		// glPushMatrix();
		// 	glTranslatef(sp, sp, 0);
		// 	glRotatef(-lookOrientation[1], 1, 0, 0);
		// 	glRotatef(-lookOrientation[0], 0, 1, 0);
		// 	drawUnitGimbal(1.0, 1.0, 1.0);
		// glPopMatrix();

// MIDDLE ROW

		glPushMatrix();
			glTranslatef(-sp, 0, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(-lookOrientation[1], 1, 0, 0);
			glRotatef(-lookOrientation[0], 0, 0, 1);
			drawUnitGimbal(1.0, 1.0, 1.0);
			label3DAxes(1);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			glRotatef(-lookOrientation[1], 1, 0, 0);
			glRotatef(-lookOrientation[0], 0, 0, 1);
			drawUnitGimbal(1.0, 1.0, 1.0);
			glMultMatrixf(orientationMatrix);
			drawUnitGimbal(0.5, 0.5, 1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(sp, 0, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(-lookOrientation[1], 1, 0, 0);
			glRotatef(-lookOrientation[0], 0, 0, 1);
			drawUnitGimbal(1.0, 1.0, 1.0);
			float orient2[16];
			mat3ToMat4(geographicLatMatrix, orient2);
			glMultMatrixf(orient2);
			drawUnitGimbal(1.0, 0.0, 0.0);
		glPopMatrix();

// BOTTOM ROW
		// glPushMatrix();
		// 	glTranslatef(-sp, -sp, 0);
		// 	glRotatef(-lookOrientation[1], 1, 0, 0);
		// 	glRotatef(-lookOrientation[0], 0, 1, 0);
		// 	drawUnitGimbal(1.0, 1.0, 1.0);
		// glPopMatrix();

		// glPushMatrix();
		// 	glTranslatef(0, -sp, 0);
		// 	glRotatef(-lookOrientation[1], 1, 0, 0);
		// 	glRotatef(-lookOrientation[0], 0, 1, 0);
		// 	drawUnitGimbal(1.0, 1.0, 1.0);
		// glPopMatrix();

		// glPushMatrix();
		// 	glTranslatef(sp, -sp, 0);
		// 	glRotatef(-lookOrientation[1], 1, 0, 0);
		// 	glRotatef(-lookOrientation[0], 0, 1, 0);
		// 	drawUnitGimbal(1.0, 1.0, 1.0);
		// glPopMatrix();

	glPopMatrix();

}


void draw2D(){
	char string[35];
	sprintf(string, "Lat:%.2f, Lon:%.2f", observerLat, observerLon);   
	text(string, 0, 20, 0);
}
void keyDown(unsigned int key){ }
void keyUp(unsigned int key){ }
void mouseDown(unsigned int button){ }
void mouseUp(unsigned int button){ }
void mouseMoved(int x, int y){ }

void drawUnitGimbal(float red, float green, float blue){
	float a1 = 1.0;
	float a2 = 0.333;
	glPushMatrix();
		// equator
		glColor4f(red, green, blue, a1);
			drawUnitCircle(0, 0, 0);
		// latitude
		glColor4f(red, green, blue, a2);
		for(float pos = 1.0/3; pos < 1.0; pos += 1.0/3){
			glPushMatrix();
				float r = cosf(pos*M_PI*0.5);
				r = sqrt(1 - powf(pos,2));
				glScalef(r, r, 1.0);
					drawUnitCircle(0, 0, -pos);
					drawUnitCircle(0, 0, pos);
			glPopMatrix();
		}
		// longitude
		glColor4f(red, green, blue, a1);
			glRotatef(90, 0, 1, 0);
			drawUnitCircle(0, 0, 0);
		glColor4f(red, green, blue, a2);
			glRotatef(30, 1, 0, 0);
			drawUnitCircle(0, 0, 0);
			glRotatef(30, 1, 0, 0);
			drawUnitCircle(0, 0, 0);
		glColor4f(red, green, blue, a2);
			glRotatef(30, 1, 0, 0);
			drawUnitCircle(0, 0, 0);
		glColor4f(red, green, blue, a2);
			glRotatef(30, 1, 0, 0);
			drawUnitCircle(0, 0, 0);
			glRotatef(30, 1, 0, 0);
			drawUnitCircle(0, 0, 0);
	glPopMatrix();
	glColor4f(red, green, blue, a1);
	draw3DAxesLines(0,0,0,1.5);
	glColor4f(1.0, 1.0, 1.0, 1.0);
}



void drawWorldAxes(){
	int scale = 10;
	for(int i = -scale; i <= scale; i+=scale){
		for(int j = -scale; j <= scale; j+=scale){
			for(int k = -scale; k <= scale; k+=scale){
				GLfloat material[] = { 1.0, 1.0, 1.0, 0.2 };
				glColor4f(1.0, 1.0, 1.0, 0.2);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, material);
				draw3DAxesLines(i, j, k, 1.0);
			}
		}
	}
}
