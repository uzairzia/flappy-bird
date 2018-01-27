/*
Assignment 2
Date 22/11/2015

Submmited to :
Sir Shamayl Bin Mansoor
Submitted by :
Name : Muhammad Rafah Mehfooz
Merit No. 1129

Name : Uzair Zia
Merit No. 894
*/

#define _CRT_SECURE_NO_WARNINGS
#include < stdlib.h> 
#include "glut.h"
#include <stdio.h>
#include <conio.h>
#include <math.h> //for drawing circle
#include <Windows.h> //For Sound

#include <mmsystem.h>//For Sound

#define M_PI 3.14159265358979323846f

/*define size of the window*/
int g_Width = 400;
int g_Height = 400;

/*global mouse position*/
int mouse_X = 0;    //xcod
int mouse_Y = 0;    //ycodz
					/*pipe1*/
int pipe1_x = 300;        //pipe 1 x cordinates
int pipe1_y[2] = { 0, 150 };        //pipe 1 y  cordinates
									/*pipe2*/
int pipe2_x = 300;                    //pipe 2 x cordinates
int pipe2_y[2] = { 250, 400 };        //pipe 2 y  cordinates
									  /*pipe3*/
int pipe3_x = 700;                    //pipe 1 x cordinates
int pipe3_y[2] = { 0, 100 };        //pipe 1 y  cordinates
									/*pipe4*/
int pipe4_x = 700;                    //pipe 2 x cordinates
int pipe4_y[2] = { 200, 400 };        //pipe 2 y  cordinates


									  //Scores
int score = 0;
int high_score;

/*circle*/
int c_x = 50, c_y = 300, c_speed = 0;
double c_direction = 0.0;


void init();

void myKeyboardFunction(unsigned char key, int mouseX, int mouseY);        /*Keyboard Keys*/
void mySpecialKeysFunction(int key, int x, int y);                        /*Special Keyboard Keys*/
void myReshapeFunction(int width, int height);
void myTimerFunction(int val);                                            /*Frames Per Second, Screen Refresh Rate*/
void myDisplayFunction();                                                /*Everything Appearing on Screen*/
																		 //Circle
void draw_circle(int x, int y, int radius) {
	float angle;
	glLineWidth(1.0f);
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.3, 0.6);                                        //to display colored objects
	for (int i = 0; i < 100; i++) {
		angle = i * 2 * M_PI / 100;
		glVertex2f(x + (cos(angle)* radius), y + (sin(angle)*radius));

	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < 100; i++) {
		angle = i * 2 * M_PI / 100;
		glVertex2f(x + 7 + (cos(angle) * 7), y - 5 + (sin(angle) * 5));
	}
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < 100; i++) {
		angle = i * 2 * M_PI / 100;
		glVertex2f(x + 8 + (cos(angle) * 2), y - 5 + (sin(angle) * 2));
	}
	glEnd();

	glLineWidth(10);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 100; i++) {
		angle = i * 2 * M_PI / 100;
		glVertex2f(x + 10 + (cos(angle) * 9), y + 7 + (sin(angle) * 4));
	}
	glEnd();

	glLineWidth(10);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < 100; i++) {
		angle = i * 2 * M_PI / 100;
		glVertex2f(x - 12 + (cos(angle) * 7), y + 2 + (sin(angle) * 3));
	}
	glEnd();
}
//Printing in the GLUT Window
void renderBitmapString(
	float x,
	float y,
	char *string) {

	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

/*RESET GAME*/
void reset() {

	//ball reset
	c_x = 50;
	c_y = 300;
	c_speed = 0;
	c_direction = 0;

	//score reset
	score = 0;

	//top pipe1 reset
	pipe1_x = 300;            //pipe 1 x cordinates
	pipe1_y[0] = 0;            //pipe 1 y  cordinates
	pipe1_y[1] = 150;

	//bottom pipe2 reset
	pipe2_x = 300;            //pipe 2 x cordinates
	pipe2_y[0] = 250;        //pipe 2 y  cordinates
	pipe2_y[1] = 400;

	//top pipe3 reset
	pipe3_x = 700;            //pipe 3 x cordinates
	pipe3_y[0] = 0;            //pipe 3 y  cordinates
	pipe3_y[1] = 100;

	//bottom pipe4 reset
	pipe4_x = 700;            //pipe 4 x cordinates
	pipe4_y[0] = 200;        //pipe 4 y  cordinates
	pipe4_y[1] = 400;
}

/*Main Body*/
int main(int argc, char** argv)
{
	int w = 800;
	int h = 400;
	glutInit(&argc, argv);                                            //initilize the GLUT libraray
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);                    //has four colour components red, green,blue, and alpha 
	glutInitWindowSize(w, h);                                        //size of window
	glutInitWindowPosition(0, 0);                                    //poistion of window
	glutCreateWindow("FLAPPY BIRD REBORN");                                //Title of Application

	init();


	glutKeyboardFunc(myKeyboardFunction);                            //Calling Keyboard Function
	glutSpecialFunc(mySpecialKeysFunction);                            //Calling Spcecial Keyboard Function

	glutReshapeFunc(myReshapeFunction);
	glutDisplayFunc(myDisplayFunction);                                //Calling Display Function
	glutTimerFunc(60, myTimerFunction, 0);

	//glutFullScreen();                                                // make the screen fullscreen
	glutSetCursor(GLUT_CURSOR_INFO);                                //Displays the type of cursor u want

	glutMainLoop();

	return 0;
}

void init(void)
{
	/*Some Predefined Functions to Start*/
	glClearColor(0.6, 0.7, 0.8, 0.0);        //background color of openGl window        red, green, blue, alpha(opaquenss) 
	glMatrixMode(GL_PROJECTION);            //glMatrixMode — specify which matrix is the current matrix ????
	glLoadIdentity();                        //glLoadIdentity — replace the current matrix with the identity matrix    ????

	glOrtho(0.0, g_Width, 0.0, g_Height, -1.0, 1.0);    //set (0,0) on left top
}

void myKeyboardFunction(unsigned char key, int mouseX, int mouseY)
{

	//Restart game
	if (key == 'r') { reset(); }

}

void mySpecialKeysFunction(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		c_y -= 25;
		c_direction = 1;

		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_HOME:
		break;
	case GLUT_KEY_END:
		break;
	case GLUT_KEY_PAGE_UP:
		break;
	case GLUT_KEY_PAGE_DOWN:
		break;

	}
}

void myReshapeFunction(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT);

	g_Width = width;
	g_Height = height;

	glViewport(0, 0, g_Width, g_Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, g_Width, g_Height, 0.0, -1.0, 1.0);        //change the (0,0) to top left
}

void myTimerFunction(int val)
{
	glutTimerFunc(33, myTimerFunction, 0);                    //Refresh Rate
	myDisplayFunction();
}

void myDisplayFunction()
{
	glClear(GL_COLOR_BUFFER_BIT);                            //clers the screen after display


	glBegin(GL_QUADS);
	glColor3f(0.0, 0.3, 0.1);                        //to display colored objects
	glVertex2f(pipe1_x, pipe1_y[0]);                //f( 300 ,0 )    
	glVertex2f(pipe1_x, pipe1_y[1]);                //f( 300 ,150 ) 
	glVertex2f(pipe1_x + 50, pipe1_y[1]);            //f( 350 ,150 ) 
	glVertex2f(pipe1_x + 50, pipe1_y[0]);            //f( 350 ,0 ) 
	glEnd();

	pipe1_x -= 5;                                    // Pipe 1 moving axis
	if (pipe1_x + 50 == 0) {                            // if block x -axis = 0 then start again x-axis = max
		pipe1_x = 800;
		pipe1_y[1] = rand() % 150;
	}

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.3, 0.1);                        //to display colored objects
	glVertex2f(pipe2_x, pipe2_y[0]);                //f( 300 ,250 )    
	glVertex2f(pipe2_x, pipe2_y[1]);                //f( 300 ,400 ) 
	glVertex2f(pipe2_x + 50, pipe2_y[1]);            //f( 350 ,400 ) 
	glVertex2f(pipe2_x + 50, pipe2_y[0]);            //f( 350 ,250 ) 

	glEnd();
	pipe2_x -= 5;                                    // Pipe 2 moving axis
	if (pipe2_x + 50 == 0) {                            // if block x -axis = 0 then start again x-axis = max
		pipe2_x = 800;
		pipe2_y[0] = pipe1_y[1] + 75;
	}

	//pipe 4
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.3, 0.1);                        //to display colored objects
	glVertex2f(pipe4_x, pipe4_y[0]);                //f( 700 ,200 )    
	glVertex2f(pipe4_x, pipe4_y[1]);                //f( 700 ,400 ) 
	glVertex2f(pipe4_x + 50, pipe4_y[1]);            //f( 750 ,400 ) 
	glVertex2f(pipe4_x + 50, pipe4_y[0]);            //f( 750 ,200 ) 

	glEnd();
	pipe4_x -= 5;                                    // Pipe 4 moving axis
	if (pipe4_x + 50 == 0) {                            // if block x -axis = 0 then start again x-axis = max
		pipe4_x = 800;
		pipe4_y[0] = rand() % 100 + 300;
	}

	// pipe 3 
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.3, 0.1);                        //to display colored objects
	glVertex2f(pipe3_x, pipe3_y[0]);                //f( 700 ,0 )    
	glVertex2f(pipe3_x, pipe3_y[1]);                //f( 700 ,100 ) 
	glVertex2f(pipe3_x + 50, pipe3_y[1]);            //f( 750 ,100 ) 
	glVertex2f(pipe3_x + 50, pipe3_y[0]);            //f( 750 ,0 ) 

	glEnd();
	pipe3_x -= 5;                                    // Pipe 3 moving axis
	if (pipe3_x + 50 == 0) {                            // if block x -axis = 0 then start again x-axis = max
		pipe3_x = 800;
		pipe3_y[1] = pipe4_y[0] - 75;
	}

	draw_circle(c_x += c_speed, c_y += c_direction, 15); //Drawing Bird

														 //top pipe 1 collision
	if ((c_x + 15 >= pipe1_x && c_x - 15 <= pipe1_x + 50) && (c_y + 15 >= pipe1_y[0] && c_y - 15 <= pipe1_y[1])) {
		PlaySound(LPCWSTR("http://www.myinstants.com/media/sounds/sfx_point.mp3"), NULL, SND_ASYNC | SND_FILENAME);
		reset();
	}
	//top pipe 2 collision
	if ((c_x + 15 >= pipe2_x && c_x - 15 <= pipe2_x + 50) && (c_y + 15 >= pipe2_y[0] && c_y - 15 <= pipe2_y[1])) {
		PlaySound(LPCWSTR("http://www.myinstants.com/media/sounds/sfx_point.mp3"), NULL, SND_ASYNC | SND_FILENAME);
		reset();
	}
	//top pipe 3 collision
	if ((c_x + 15 >= pipe3_x && c_x - 15 <= pipe3_x + 50) && (c_y + 15 >= pipe3_y[0] && c_y - 15 <= pipe3_y[1])) {
		PlaySound(LPCWSTR("http://www.myinstants.com/media/sounds/sfx_point.mp3"), NULL, SND_ASYNC | SND_FILENAME);
		reset();
	}
	//top pipe 4 collision
	if ((c_x + 15 >= pipe4_x && c_x - 15 <= pipe4_x + 50) && (c_y + 15 >= pipe4_y[0] && c_y - 15 <= pipe4_y[1])) {
		PlaySound(LPCWSTR("http://www.myinstants.com/media/sounds/sfx_point.mp3"), NULL, SND_ASYNC | SND_FILENAME);
		reset();
	}
	//Score pipe 1 & 2
	if ((c_x > pipe1_x && c_x < pipe1_x + 50) && (c_y > pipe1_y[1] && c_y < pipe2_y[0])) {
		if (c_x == pipe1_x + 25)
			score++;
		PlaySound(LPCWSTR("http://www.myinstants.com/media/sounds/sfx_point.mp3"), NULL, SND_ASYNC | SND_FILENAME);
	}

	//Score Pipe 3 & 4
	if ((c_x > pipe3_x && c_x < pipe3_x + 50) && (c_y > pipe3_y[1] && c_y < pipe4_y[0])) {
		if (c_x == pipe3_x + 25)
			score++;
		PlaySound(LPCWSTR("http://www.myinstants.com/media/sounds/sfx_point.mp3"), NULL, SND_ASYNC | SND_FILENAME);
	}

	//flap speed control
	c_direction += 0.45;

	//High score Calculation
	if (high_score < score) {
		high_score = score;
	}
	else if (high_score >= score) {
		high_score = high_score;
	}

	//Reset GAME if top and bottom boundary collisions
	if (c_y <= 0) {
		reset();
	}
	else if (c_y >= 400) {
		reset();
	}


	//text printing
	char stext[10];    //stext= scoretext

	renderBitmapString(10, 20, "Tap top Arrow Key to FLY Flappy");
	renderBitmapString(10, 40, "Total Score:");
	renderBitmapString(110, 40, _itoa(score, stext, 10));
	renderBitmapString(10, 60, "High Score:");
	renderBitmapString(110, 60, _itoa(high_score, stext, 10));

	glutSwapBuffers();                                        //brings the openGl window on the front
	printf("\n.");


}