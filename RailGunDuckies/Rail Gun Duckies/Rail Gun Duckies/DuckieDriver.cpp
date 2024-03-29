/* The DuckieDriver file is a testing file for the Duckie class
   and its functions. */ 

#include <GL/freeglut.h>
#include "Duckie.h"
#include "RailGun.h"
#include "Balloon.h"
#include "Window.h"
#include "Scene.h"
#include <stdio.h>  
#include <iostream>
#include <sstream> //Checka
#include <vector>
#include <assert.h> //Checkb

using namespace std;

const int init_width = 1280;
const int init_height = 720;

int window_width = init_width;
int window_height = init_height;

double aspect = 1;

bool isWireFrame = false;
bool paused = false;
bool isFullScreen = false;
bool duckFullSize = false;

double period = 1000/60;

double pScale = .01;

//the test subjets:
Window * w;
Duckie  d;
Duckie p;
Balloon b;
RailGun r;

Scene s;


//angle of rotation for camera
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, zrot = 0.0, angle=0.0;
void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh 
									//x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the 
									//	y-axis (up and down)
	glRotatef(zrot, 0, 0, 1);
    glTranslated(-xpos,-ypos,-zpos); //translate the screen
									// to the position of our camera
}

//function for displaying informational text in an
// orthographic projection. 
void displayText(string text) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_width, 0, window_height, 1, 10); // set ortho projection based on window size
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//starting from the bottom left corner, translate text 10 units
	// up and step back to see it. Scale to desired size
	glTranslatef(0, 10, -1);
	glScalef(0.25f, 0.25f, 1.0f);
	glDisable(GL_LIGHTING); //make sure to disable lighting!
	glColor3f(1, 1, 1);

	//freeglut uses c style strings, so we need to get that.
	const char * c = text.c_str();
	//and actually print the string:
	glutStrokeString(GLUT_STROKE_MONO_ROMAN, (unsigned char *)c);

	glEnable(GL_LIGHTING); //enable lighting since we're done
}


bool CheckGLErrors() {
	bool error_found = false;
	GLenum  error;
	const GLubyte *errorString;
	while ((error = glGetError()) != GL_NO_ERROR) {
		error_found = true;
		errorString = gluErrorString(error);
		cout << errorString;
	}

	return error_found;
}

//InitGL function to handle all GL initializations
// for the main function. Handles lighting and depth so far...
void initGL() {

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE , 0.0);
	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER , 1.0);

	//////set up light position
	GLfloat light_position[] = { 2 , 2, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


}

void SwitchingDisplayFunc() {
	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//set up the world so we can see stuff!
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, w->getAspect(), 1, 250);
	glViewport(0, 0, w->getWidth(), w->getHeight());
	//glPushMatrix();
	//glScaled(.01, .01, .01);
	//glTranslated(0, 0, -500);
	//glRotated(0, 0, 1, 0);
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, (unsigned char *)"Adam Sperling");
	//glPopMatrix();
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
	//glTranslated(0, 0, -5);
//	gluLookAt(0, 5, -5, 0, 0, 0, 0, 1, 0);
//	camera();
//	glRotated(elapsed_time * 60, 0, 1, 0);

	switch (w->getSceneMode()) {

	case DUCK_BEAUTY:
		s.runBeautyMode(DUCK_BEAUTY);
		displayText("Duck Beauty Mode");
	//	s.duckBeauty();
		/*glPushMatrix();
		glTranslated(-3, 0, 0);
		g.render();
		glPopMatrix();
		glPushMatrix();
		glTranslated(3, 0, 0);
		d.render();
		glPopMatrix();*/
		break;

	case RAILGUN_BEAUTY:
		s.runBeautyMode(RAILGUN_BEAUTY);
		displayText("RailGun Beauty Mode");
	//	s.railGunBeauty();
		//glPushMatrix();
		//r.render();
		//glPopMatrix();
		break;

	case BALLOON_BEAUTY:
		s.runBeautyMode(BALLOON_BEAUTY);
		displayText("Balloon Beauty Mode");
	//	s.balloonBeauty();
		//glPushMatrix();
		//b.render();
		//glPopMatrix();
		break;

	case GAME:

		s.runGameMode(false, elapsed_time);
	/*	glPushMatrix();
		s.renderWorld();
		glPopMatrix();*/
		break;

	case GAME_FOREVER:
	//	s.runGameMode(true);
		break;

	default: break;

	}

	glutSwapBuffers();
	glutPostRedisplay();
}
//void DuckieDisplayFunc() {
//	// use a switch to toggle between modes
//	// each mode has a separate function
//
//	double elapsed_time = double(glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
//	
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glClearColor(1, 1, 1, 0);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	//set up the world so we can see stuff!
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
////	glOrtho(-3 * aspect, 3 * aspect, -3, 3, 1, 10);
//	gluPerspective(60, aspect, 1, 20);
//	glViewport(0, 0, window_width, window_height);
//	
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glTranslated(0, 0, -8);
//	camera();
////	glRotated(elapsed_time * 60, 0, 1, 0);
//	glPushMatrix();
//	
//	b.render();
////	b.drawDiamond();
////	b.Triangle();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(-3, 0, 0);
////	glRotated(elapsed_time * 60, 0, -1, 1);
//	d.render();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(3, 0, 0);
//	d.render();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0, 0, 3);
//	d.render();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslated(0, 0, -3);
//	d.render();
//	glPopMatrix();
//
//	//RailGun * basic = new RailGun();
///*
//	glPushMatrix();
//	glTranslated(0, 0, -5);
//	glTranslated(-3, 0, 0);
//	glRotated(elapsed_time * 60, 0, 1, 0);
//
//
//	d.render();
//
//	//basic->render();
//
//
//	glPopMatrix();
//
//	
//
//	glPushMatrix();
//	glTranslated(0, 0, -5);
//	glTranslated(3, 0, 0);
//	glRotated(elapsed_time * 60, 1, 0, 0);
//
//	// grow the duck
//	if (pScale <= 1) {
//		glScaled(pScale, pScale, pScale);
//		pScale += .001;
//	}
//
//	p.render();
////	basic->render();
//
////	delete basic;
//
//	glPopMatrix();
//*/
//	
//	glutSwapBuffers();
//	glutPostRedisplay();
//}

void ReshapeFunc(int width, int height) {
	
	w->reshape(width, height);
	/*if (height <= 0) {
		return;
	}

	window_width = width;
	window_height = height;


	aspect = double(width) / double(height);*/ // remember to guard against div/0
}

void KeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
	
	case 'f':
		w->toggleFullScreen();
		break;
		
	case 'w':
		w->toggleWireFrame();
		break;

	case 'l':
		w->toggleLights();
		break;

	case 'p': 
		paused = !paused;
		break;
		// need to keep track of elapsed time while pasued and subtract from total time

	case 32: //spacebar
		if (w->getSceneMode() == GAME || w->getSceneMode() == GAME_FOREVER)
			s.fire();
	break;

	case 'x':
	case 27: 
		glutLeaveMainLoop();
		delete w;
		return;
	}
}

void SpecialFunc(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		w->cycleSceneMode();
		break;

	case GLUT_KEY_F2:
		w->cycleLightingMode();
		break;

	//useing arrow keys to control camera for now
	case GLUT_KEY_LEFT:
		yrot -= 1;
		if (yrot < -360) yrot += 360;
		break;

	case GLUT_KEY_RIGHT: 
		yrot += 1;
		if (yrot < -360) yrot -= 360;
		break;

	case GLUT_KEY_UP:
		xrot += 1;
		if (xrot < -360) xrot -= 360;
		break;

	case GLUT_KEY_DOWN:
		xrot -= 1;
		if (xrot < -360) xrot -= 360;
		break;
	
	default: break;
	}
}
void TimerFunc(int value) {
	glutTimerFunc(GLuint(period), TimerFunc, value);
	glutPostRedisplay();
}
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	/*
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(init_width, init_height);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		glutCreateWindow("Driver");
	 */
	w = new Window();

	initGL();

	glutDisplayFunc(SwitchingDisplayFunc);
	glutReshapeFunc(ReshapeFunc); // what function called if resized window?
	glutKeyboardFunc(KeyboardFunc); // what function called if keypressed?
	glutTimerFunc(GLuint(period), TimerFunc, 0);
	glutSpecialFunc(SpecialFunc);
	glutMainLoop();
	return 0;
}
