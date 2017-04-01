#include "../lib/world.h"
#include "../stargaze.h"

void drawUnitGimbal(float red, float green, float blue);
void drawWorldAxes();

float axialTiltMatrix[9];
float axialTiltMatrixPrime[9];

float observerLat = 18.45;  // degrees
float observerLon = -66.0;  // degrees
// double eclipticLat = 97.638119;  // degrees
// double eclipticLon = -17.857969; // degrees
// double siderealTime = 5.155862;  // hours
// double STDeg = siderealTime*15;  // degrees
// double siderealDeg = siderealTime * 15; // degrees
// eclipticToHorizontal(eclipticLat, eclipticLon, observerLat, siderealDeg, &azimuth, &altitude);

int year = 2016;
int month = 12;
int day = 21;
int hour = 0;
int minute = 0;
int second = 0;

void setup(){
	emptyPerspective();
	GROUND = 0;
	GRID = 0;
	generateAxialTiltMatrix(axialTiltMatrix);
	generateAxialTiltMatrixPrime(axialTiltMatrixPrime);
}
void update(){
	if(keyboard[']']){
		observerLon += 0.5;
	} if(keyboard['[']){
		observerLon -= 0.5;
	}

	if(keyboard[';']){
		observerLat += 0.5;
	} if(keyboard['\'']){
		observerLat -= 0.5;
	}

}

void draw3D(){

	glPushMatrix();
	float sp = 4;

// TOP ROW
		glPushMatrix();
			glTranslatef(-sp, sp*0.5, 0);
			// text("Earth", -1.0, 1.6, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(-lookOrientation[1], 1, 0, 0);
			glRotatef(-lookOrientation[0], 0, 0, 1);
			label3DAxes(1);
			drawUnitGimbal(0.5, 0.5, 0.5);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, sp*0.5, 0);
			text("Sidereal Time + Longitude", -1.0, -1.6, 0);
			text("Now time", -0.8, -1.8, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(-lookOrientation[1], 1, 0, 0);
			glRotatef(-lookOrientation[0], 0, 0, 1);
			drawUnitGimbal(0.5, 0.5, 0.5);
			glPushMatrix();
				float topCenterMatrix[16];
				float siderealNowMatrix[9];
				double J2000Now = J2000DaysFromUTCNow();
				double siderealNow = localMeanSiderealTime(J2000Now, observerLon);
				generateSiderealTimeMatrix(siderealNowMatrix, siderealNow);
				mat3ToMat4(siderealNowMatrix, topCenterMatrix);
				glMultMatrixf(topCenterMatrix);
				drawUnitGimbal(0.3, 0.3, 1.0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(sp, sp*0.5, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(-lookOrientation[1], 1, 0, 0);
			glRotatef(-lookOrientation[0], 0, 0, 1);
			drawUnitGimbal(0.5, 0.5, 0.5);
			glPushMatrix();
				float leftCenterMatrix[16];
				float siderealDateMatrix[9];
				double J2000Time = J2000DaysFromUTCTime(year, month, day, hour, minute, second);
				double siderealDate = localMeanSiderealTime(J2000Time, observerLon);
				generateSiderealTimeMatrix(siderealDateMatrix, siderealDate);
				mat3ToMat4(siderealDateMatrix, leftCenterMatrix);
				glMultMatrixf(leftCenterMatrix);
				drawUnitGimbal(0.3, 0.3, 1.0);
			glPopMatrix();
		glPopMatrix();

// BOTTOM ROW

		glPushMatrix();
			glTranslatef(-sp, -sp*0.5, 0);
			text("Earth axial tilt", -0.8, 1.6, 0);
			text("blue=prime", -0.8, 1.8, 0);
			text("rotate around X", -0.8, 2.0, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(-lookOrientation[1], 1, 0, 0);
			glRotatef(-lookOrientation[0], 0, 0, 1);
			label3DAxes(1);
			drawUnitGimbal(0.5, 0.5, 0.5);
			glPushMatrix();
				float axialTilt16[16];
				mat3ToMat4(axialTiltMatrix, axialTilt16);
				glMultMatrixf(axialTilt16);
				drawUnitGimbal(1.0, 0.0, 0.0);
			glPopMatrix();
			glPushMatrix();
				float axialTiltPrime16[16];
				mat3ToMat4(axialTiltMatrixPrime, axialTiltPrime16);
				glMultMatrixf(axialTiltPrime16);
				drawUnitGimbal(0.3, 0.3, 1.0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, -sp*0.5, 0);
			text("Latitude N 45", -1.0, 1.6, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(-lookOrientation[1], 1, 0, 0);
			glRotatef(-lookOrientation[0], 0, 0, 1);
			drawUnitGimbal(0.5, 0.5, 0.5);
			glPushMatrix();
				float geographicLat1Matrix[9];
				generateGeographicLatitudeMatrix(geographicLat1Matrix, 45);
				float bottomMidMatrix[16];
				mat3ToMat4(geographicLat1Matrix, bottomMidMatrix);
				glMultMatrixf(bottomMidMatrix);
				drawUnitGimbal(1.0, 0.0, 0.0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(sp, -sp*0.5, 0);
			char latString[35];
			sprintf(latString, "Latitude %.2f", observerLat);   
			text(latString, -1.0, 1.6, 0);
			glRotatef(-90, 1, 0, 0);
			glRotatef(-lookOrientation[1], 1, 0, 0);
			glRotatef(-lookOrientation[0], 0, 0, 1);
			drawUnitGimbal(0.5, 0.5, 0.5);
			glPushMatrix();
				float geographicLat2Matrix[9];
				generateGeographicLatitudeMatrix(geographicLat2Matrix, observerLat);
				float bottomRightMatrix[16];
				mat3ToMat4(geographicLat2Matrix, bottomRightMatrix);
				glMultMatrixf(bottomRightMatrix);
				drawUnitGimbal(1.0, 0.0, 0.0);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();

}


void draw2D(){
	char string[35];
	sprintf(string, "Lat:%.2f, Lon:%.2f", observerLat, observerLon);   
	text(string, 0, 20, 0);
	char dateString[35];
	sprintf(dateString, "%d %d-%d %02d:%02d", year, month, day, hour, minute);
	text(dateString, 0, 40, 0);
}
void keyDown(unsigned int key){
	if(key == 'm'){
		if(keyboard[RETURN_KEY]) month--;
		else month = (month+1)%12;
	}
	if(key == 'y'){
		if(keyboard[RETURN_KEY]) year--;
		else year++;
	}
	if(key == 'd'){
		if(keyboard[RETURN_KEY]) day = (day-1)%30;
		else day = (day+1)%30;
	}
	if(key == 'h'){
		if(keyboard[RETURN_KEY]) hour = (hour-1)%30;
		else hour = (hour+1)%30;
	}
	if(key == 'n'){
		if(keyboard[RETURN_KEY]) minute = (minute-1)%30;
		else minute = (minute+1)%30;
	}
}
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
