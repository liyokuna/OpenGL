/*
Lionel Mukuan Ciowela

We have to draw two polygon and make them move and one have to make a back flip whereas the second stand and watch it.
We have also to draw another 3-d figure, and i choose a pyramid. It goes down and then rotate itself in order to scare the two other.

*/
#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<iomanip>

#include<gl/glut.h>
using namespace std;
/* This program make the same thing as previously. We have to draw a polygon which have to walk from right to left and at the mid walk 
he have to perfom a back flip. And all of this must be maden by using a model view matrix.

/* declaration of global values
*/
float theta=360.0; // global angular value for rotation of polyman
float scale1=1.0;// global scaling value for square of polyman

float thetatr=360.0; // global angular value for rotation of triangleman
float scaletr=1.0;// global scaling value for square of triangleman

float thetawo=180.0; // global angular value for rotation of polywoman
float scalewo=1.0;// global scaling value for square of polywoman

float dx=7.0,dy=-3.0,dz=0.0;//global movement value for dx and dy of polyman
float dxwo=-6.0,dywo=-3.0,dzwo=0.0;//global movement value for dx and dy of polywoman
float dxtr=-1.0,dytr=8.0,dztr=0.0;//global movement value for dx and dy of triangleman
float deltax=0,deltay=1;//global variablefor translation the feet
int frame=1;

void init(void); // this function to initiliaze the window clear color
void ground(void);//design the ground
void RenderScene(void);//this function to draw a square in an opened window
void loadPolyman(float[][6], float[][6],float[][6],float [][3], float [][3],float[][3],
	float [][3], float [][3],float[][3],float, float,float, float[][3], float[][3],float[][3]); //loads the polyman icon

void loadTriangle(float[4], float[4],float[4],float [][4], float [][4],float[][4]); //loads the triangle icon
void drawTriangle(float [4], float [4],float [4],float [][4], float [][4],float [][4]);// draw the triangle icon

void loadPolywoman(float[][6], float[][6],float[][6],float [][3], float [][3],float[][3],
	float [][3], float [][3],float[][3],float, float,float, float[][3], float[][3],float[][3]); //loads the polywoman icon
void drawPolyman(float[][6], float[][6],float[][6],
float[][3],float[][3],float[][3],
float[][3],float[][3],float[][3],
float, float,float, 
float[][3],float[][3],float [][3]);// draws the icon

void drawPolywoman(float[][6], float[][6],float[][6],
float[][3],float[][3],float[][3],
float[][3],float[][3],float[][3],
float, float,float, 
float[][3],float[][3],float [][3]);// draws the icon

//void drawPolyman(float pxp[], float pyp[], float flx[], float fly[])
void settrans(float[][3], float,float,float); // sets the transformation matrix for desired scale, rotation, new pos
void settransPolyWo(float[][3], float,float,float); // sets the transformation matrix for desired scale, rotation, new pos
void settransground(void); // sests the transformation matrix for translation the foot
void settransTr(float , float,float,float ); // settrans triangle

void drawmouth(float[], float[]);
void SetupRC(void);//sets up the clear color
void TimerFunction(int );// thsi call back function is call each 30 ms and changes the location, scale and rotation

// the main program
int main(int argc, char** argv)
{
	char header[]="Polyman by Lionel Mukuna Ciowela";
	glutInit(&argc, argv);// set up the display mode with a single buffer and RGB colors
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
	// Initialize window size and position
	glutInitWindowSize(560,400);
	glutInitWindowPosition(140,20);
	
	//Open and Label Window
	glutCreateWindow(header);
	glutDisplayFunc(RenderScene);
	glutTimerFunc(30,TimerFunction,1);

	//initilaize background color in window to grey
	SetupRC();

	//Now draw the scene
	glutMainLoop();
	
	return 0;
}

void RenderScene(void)
{
	//--------------Polyman coordonates
	float xdel=0.5,eyex=-1/2.0,eyey=3/8.0,eyez=-0.6;
	float px[2][6],py[2][6],pz[2][6],flx[2][3],fly[2][3],flz[2][3],
		frx[2][3],fry[2][3],frz[2][3],mouthx[2][3], mouthy[2][3],mouthz[2][3];
	// These variables hold the pattern for square icon. 
	//Note that px,py hold the square, plx,ply hold the line
	float pxp[2][6], pyp[2][6],pzp[2][6], flxp[2][3],flyp[2][3],flzp[2][3],
		frxp[2][3],fryp[2][3],frzp[2][3], t[3][3],t2[3][3];
	//-------Polywoman coordinates--------------
	float xdelPolyW=0.5,eyePolyWox=-1/2.0,eyePolyWoy=3/8.0,eyePolyWoz=-0.6;

	float polyWox[2][6],polyWoy[2][6],polyWoz[2][6],flPolyWx[2][3],flPolyWy[2][3],flPolyWz[2][3],
		frPolyWx[2][3],frPolyWy[2][3],frPolyWz[2][3];
	 
	//-------Triangle coordinates--------------

	float sqx[4],sqy[4],sqz[4],trix[4][4],triy[4][4],triz[4][4];

	// Clear the window with the current background color
	cout<<"in renderscene"<<endl;
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();

	// set the viewport to the window dimensions
	glViewport(0,0,558,400);
	
	//Etablish the clipping volumn in user units
	//First clar all tranlsation matricies
	glOrtho(-7.0,7.0,-7.0,7.0,7.0,-7.0);

	
	// set the current drawing color to white

	loadPolywoman(polyWox,polyWoy,polyWoz,flPolyWx,flPolyWy,flPolyWz,frPolyWx,frPolyWy,frPolyWz,eyePolyWox,eyePolyWoy,eyePolyWoz,mouthx,mouthy,mouthz);

	loadPolyman(px,py,pz,flx,fly,flz,frx,fry,frz,eyex,eyey,eyez,mouthx,mouthy,mouthz);

	loadTriangle( sqx, sqy ,sqz,trix,triy,triz);

	//Draw the icon untransformed

	glEnable(GL_DEPTH_TEST);

	// Clear the window with the background color
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//now draw the ground
	settransground();
	ground();
	// draw the triangle

	settransTr(thetatr ,dxtr, dytr, dztr);
	drawTriangle( sqx, sqy,sqz,trix,triy,triz);

	settransPolyWo(t, scalewo, dxwo,dywo);

	drawPolywoman(polyWox,polyWoy,polyWoz,flPolyWx,flPolyWy,flPolyWz,frPolyWx,frPolyWy,frPolyWz,0.5,eyePolyWoy,eyePolyWoz,mouthx,mouthy,mouthz);
	//Set the current drawing color to brown
	settrans(t, scale1, dx,dy);

	// now draw the square
	drawPolyman(px,py,pz,flx,fly,flz,frx,fry,frz,eyex,eyey,eyez,mouthx,mouthy,mouthz);

	// draw the mouth
	// drawmouth(mouthx,mouthy);

	glEnd();
	
	glutSwapBuffers();

	return;
}// end of render scene

//----Trianglman

void loadTriangle(float px[4], float py[4],float pz[4],float tx[][4], float ty[][4],float tz[][4])
{

	//the square
	px[0]=-5.0/8.0; py[0]=5.0/8.0;pz[0]=-0.5;
	px[1]=5.0/8.0; py[1]=5.0/8.0;pz[1]=-0.5;
	px[2]=5.0/8.0; py[2]=5.0/8.0;pz[2]=0.5;
	px[3]=-5.0/8.0; py[3]=5.0/8.0;pz[3]=0.5;

	// one part of the triangle face 1
	tx[0][0]=0.0;		ty[0][0]=0.0;		tz[0][0]=0.0;
	tx[0][1]=-5.0/8.0;	ty[0][1]=5.0/8.0;	tz[0][1]=-0.5;
	tx[0][2]=5.0/8.0;	ty[0][2]=5.0/8.0;	tz[0][2]=-0.5;

		// one part of the triangle face 2
	tx[1][0]=0.0;		ty[1][0]=0.0;		tz[1][0]=0.0;
	tx[1][1]=5.0/8.0;	ty[1][1]=5.0/8.0;	tz[1][1]=-0.5;
	tx[1][2]=-5.0/8.0;	ty[1][2]=5.0/8.0;	tz[1][2]=0.5;

		// one part of the triangle face 3
	tx[2][0]=0.0;		ty[2][0]=0.0;		tz[2][0]=0.0;
	tx[2][1]=5.0/8.0;	ty[2][1]=5.0/8.0;	tz[2][1]=0.5;
	tx[2][2]=5.0/8.0;	ty[2][2]=5.0/8.0;	tz[2][2]=-0.5;

		// one part of the triangle face 4
	tx[3][0]=0.0;		ty[3][0]=0.0;		tz[3][0]=0.0;
	tx[3][1]=-5.0/8.0;	ty[3][1]=5.0/8.0;	tz[3][1]=-0.5;
	tx[3][2]=5.0/8.0;	ty[3][2]=5.0/8.0;	tz[3][2]=0.5;

}

void drawTriangle(float px[4], float py[4],float pz[4],float tx[][4], float ty[][4],float tz[][4])
{
	cout<<"In draw triangle"<<endl;
	glColor3f(0.2,0.2,0.15);
	// square 
	glBegin(GL_POLYGON);
	//move to first point in icon
	//now draw the rest of the box
	for(int i=0;i<=3;i++)
	{
		glVertex3f(px[i],py[i],pz[i]);
	}
	glEnd();

	for(int face=0;face<3;face++)
	{
	//draw each part of the triangle
	glBegin(GL_TRIANGLES);
	for(int i=0;i<3;i++)
	{
		glColor3f(tx[face][i],ty[face][i],tz[face][i]);
		glVertex3f(tx[face][i],ty[face][i],tz[face][i]);
	}
	glEnd();


	}
}
//----------Load icon-----------------
void loadPolyman( float px[][6], float py[][6], float pz[][6], float flx[][3], float fly[][3], float flz[][3],float frx[][3],float fry[][3],float frz[][3],float eyex, float eyey,float eyez, float mouthx[][3], float mouthy[][3],float mouthz[][3]
) // this procedure loads a square icon
{
	//set the coordinates of the first polygon
	
	px[0][0]=-5.0/8.0;	py[0][0]=5.0/8.0;	pz[0][0]=-0.5;
	px[0][1]=5.0/8.0;	py[0][1]=5.0/8.0;	pz[0][1]=-0.5;
	px[0][2]=1.0;		py[0][2]=0.0;		pz[0][2]=-0.5;
	px[0][3]=5.0/8.0;	py[0][3]=-5.0/8.0;	pz[0][3]=-0.5;
	px[0][4]=-5.0/8.0;	py[0][4]=-5.0/8.0;	pz[0][4]=-0.5;
	px[0][5]=-1.0;		py[0][5]=0.0;		pz[0][5]=-0.5;

	//set the coordinates of the second polygon
	
	px[1][0]=-5.0/8.0; py[1][0]=5.0/8.0;	pz[1][0]=0.5;
	px[1][1]=5.0/8.0;  py[1][1]=5.0/8.0;	pz[1][1]=0.5;
	px[1][2]=1.0;      py[1][2]=0.0;		pz[1][2]=0.5;
	px[1][3]=5.0/8.0;  py[1][3]=-5.0/8.0;	pz[1][3]=0.5;
	px[1][4]=-5.0/8.0; py[1][4]=-5.0/8.0;	pz[1][4]=0.5;
	px[1][5]=-1.0;     py[1][5]=0.0;		pz[1][5]=0.5;

	//eyes
	eyex=-1/2.0;eyey=3/8.0;eyez=0.6;
	
	// set the mouth by drawing a triangle face 1
	mouthx[0][0]=-1/4.0; mouthy[0][0]=0.0; mouthz[0][0]=0.5;
	mouthx[0][1]=-1.0;   mouthy[0][1]=0.0;   mouthz[0][1]=0.5;
	mouthx[0][2]=-5.0/8.0;mouthy[0][2]=-5.0/8.0; mouthz[0][2]=0.5;

	// set the mouth by drawing a triangle face 2
	mouthx[1][0]=-1/4.0; mouthy[1][0]=0.0; mouthz[1][0]=-0.5;
	mouthx[1][1]=-1.0;   mouthy[1][1]=0.0;   mouthz[1][1]=-0.5;
	mouthx[1][2]=-5.0/8.0;mouthy[1][2]=-5.0/8.0; mouthz[1][2]=-0.5;

	// set leg rigth face 1
	frx[0][0]=1/8.0; fry[0][0]=-5/8.0; frz[0][0]=0.5;
	frx[0][1]=1/8.0; fry[0][1]=-3/2.0; frz[0][1]=0.5;
	frx[0][2]=-0.05; fry[0][2]=-3/2.0; frz[0][2]=0.5;

	// set leg rigth face 2
	frx[1][0]=1/8.0; fry[1][0]=-5/8.0; frz[1][0]=-0.5;
	frx[1][1]=1/8.0; fry[1][1]=-3/2.0; frz[1][1]=-0.5;
	frx[1][2]=-0.05; fry[1][2]=-3/2.0; frz[1][2]=-0.5;

	// set the leg left face 1
	flx[0][0]=-2/8.0; fly[0][0]=-4/8.0; flz[0][0]=0.5;
	flx[0][1]=-2/8.0; fly[0][1]=-3/2.0; flz[0][1]=0.5;
	flx[0][2]=-3/8.0; fly[0][2]=-3/2.0; flz[0][2]=0.5;

	// set the leg left face 2
	flx[1][0]=-2/8.0; fly[1][0]=-4/8.0; flz[1][0]=-0.5;
	flx[1][1]=-2/8.0; fly[1][1]=-3/2.0; flz[1][1]=-0.5;
	flx[1][2]=-3/8.0; fly[1][2]=-3/2.0; flz[1][2]=-0.5;

	return;
}

void drawPolyman(float pxp[][6], float pyp[][6], float pzp[][6], float flxp[][3], float flyp[][3], float flzp[][3], float frxp[][3], float fryp[][3],float frzp[][3], float eyex,float eyey,float eyez,float mouthx[][3], float mouthy[][3],float mouthz[][3])
	//this function draws the square icon at the transformed position
{
	int i;
	cout<<"in drawPolyman"<<endl;

	//draw the eyes
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex3f(eyex,eyey,eyez);
	glEnd();

	for(int face=0;face<2;face++)
	{
		glFrontFace(GL_CW);

		//glCullFace(GL_BACK);

		//glEnable(GL_CULL_FACE);

		glColor3f(0.5,0.2,0.9);
	// polygon face 1
		glBegin(GL_POLYGON);
	//move to first point in icon
	//now draw the rest of the box
		glShadeModel(GL_FLAT);
		for(i=0;i<=5;i++)
		{
			glVertex3f(pxp[face][i],pyp[face][i],pzp[face][i]);
		}
	
	}
	glEnd();
	//draw the top of the polygon
	glColor3f(0.5,0.2,0.9);
	glBegin(GL_POLYGON);
		
	glVertex3f(pxp[0][0],pyp[0][0], pzp[0][0]);
	glVertex3f(pxp[0][1],pyp[0][1], pzp[0][1]);
	glVertex3f(pxp[1][1],pyp[1][1], pzp[1][1]);
	glVertex3f(pxp[1][0],pyp[1][0], pzp[1][0]);
	
	glEnd();

	//draw the bottom of the polygon
	glColor3f(0.5,0.2,0.9);
	glBegin(GL_POLYGON);
		
	glVertex3f(pxp[0][3],pyp[0][3], pzp[0][3]);
	glVertex3f(pxp[0][4],pyp[0][4], pzp[0][4]);
	glVertex3f(pxp[1][4],pyp[1][4], pzp[1][4]);
	glVertex3f(pxp[1][3],pyp[1][3], pzp[1][3]);
	
	glEnd();

	//draw the corner right down of the polygon
	glColor3f(0.5,0.2,0.9);
	glBegin(GL_POLYGON);
		
	glVertex3f(pxp[0][2],pyp[0][2], pzp[0][2]);
	glVertex3f(pxp[0][3],pyp[0][3], pzp[0][3]);
	glVertex3f(pxp[1][3],pyp[1][3], pzp[1][3]);
	glVertex3f(pxp[1][2],pyp[1][2], pzp[1][2]);
	
	glEnd();

	//draw the corner right up of the polygon
	glColor3f(0.5,0.2,0.9);
	glBegin(GL_POLYGON);
		
	glVertex3f(pxp[0][1],pyp[0][1], pzp[0][1]);
	glVertex3f(pxp[0][2],pyp[0][2], pzp[0][2]);
	glVertex3f(pxp[1][2],pyp[1][2], pzp[1][2]);
	glVertex3f(pxp[1][1],pyp[1][1], pzp[1][1]);
	
	glEnd();

	//draw the corner left up of the polygon
	glColor3f(0.5,0.2,0.9);
	glBegin(GL_POLYGON);
		
	glVertex3f(pxp[0][0],pyp[0][0], pzp[0][0]);
	glVertex3f(pxp[0][5],pyp[0][5], pzp[0][5]);
	glVertex3f(pxp[1][5],pyp[1][5], pzp[1][5]);
	glVertex3f(pxp[1][0],pyp[1][0], pzp[1][0]);
	
	glEnd();
	//draw the corner left down of the polygon
	/*glColor3f(0.5,0.2,0.9);
	glBegin(GL_POLYGON);
		
	glVertex3f(pxp[0][5],pyp[0][5], pzp[0][5]);
	glVertex3f(pxp[0][4],pyp[0][4], pzp[0][4]);
	glVertex3f(pxp[1][4],pyp[1][4], pzp[1][4]);
	glVertex3f(pxp[1][5],pyp[1][5], pzp[1][5]);
	
	glEnd();*/

	/// now draws the foot
	//feet right face 1
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(frxp[0][0],fryp[0][0],frzp[0][0]);
	glVertex3f(frxp[0][1],fryp[0][1],frzp[0][1]);
	glVertex3f(frxp[0][2],fryp[0][2],frzp[0][2]);
	glEnd();

	//feet right face 2
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(frxp[1][0],fryp[1][0],frzp[1][0]);
	glVertex3f(frxp[1][1],fryp[1][1],frzp[1][1]);
	glVertex3f(frxp[1][2],fryp[1][2],frzp[1][2]);
	glEnd();

	//feet left face 1
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(flxp[0][0],flyp[0][0],flzp[0][0]);
	glVertex3f(flxp[0][1],flyp[0][1],flzp[0][1]);
	glVertex3f(flxp[0][2],flyp[0][2],flzp[0][2]);
	glEnd();
	//feet left face 2
	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(flxp[1][0],flyp[1][0],flzp[1][0]);
	glVertex3f(flxp[1][1],flyp[1][1],flzp[1][1]);
	glVertex3f(flxp[1][2],flyp[1][2],flzp[1][2]);
	glEnd();

	

	//draw the mouth face 1
	glColor3f(0.6f, 0.4f, 0.70f);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
	for(int i=0; i<=2;i++)
	{
	glVertex3f(mouthx[0][i],mouthy[0][i],mouthz[0][i]);
	}
	glEnd();
	//draw the mouth face 2
	glColor3f(0.6f, 0.4f, 0.70f);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
	for(int i=0; i<=2;i++)
	{
	glVertex3f(mouthx[1][i],mouthy[1][i],mouthz[1][i]);
	}
	glEnd();
	
	return;

}


//Polywoman

void loadPolywoman( float px[][6], float py[][6], float pz[][6], float flx[][3], float fly[][3], float flz[][3],float frx[][3],float fry[][3],float frz[][3],float eyex, float eyey,float eyez, float mouthx[][3], float mouthy[][3],float mouthz[][3]
) // this procedure loads a square icon
{
	//set the coordinates of the first polygon
	
	px[0][0]=-5.0/8.0;	py[0][0]=5.0/8.0;	pz[0][0]=-0.5;
	px[0][1]=5.0/8.0;	py[0][1]=5.0/8.0;	pz[0][1]=-0.5;
	px[0][2]=1.0;		py[0][2]=0.0;		pz[0][2]=-0.5;
	px[0][3]=5.0/8.0;	py[0][3]=-5.0/8.0;	pz[0][3]=-0.5;
	px[0][4]=-5.0/8.0;	py[0][4]=-5.0/8.0;	pz[0][4]=-0.5;
	px[0][5]=-1.0;		py[0][5]=0.0;		pz[0][5]=-0.5;

	//set the coordinates of the second polygon
	
	px[1][0]=-5.0/8.0; py[1][0]=5.0/8.0;	pz[1][0]=0.5;
	px[1][1]=5.0/8.0;  py[1][1]=5.0/8.0;	pz[1][1]=0.5;
	px[1][2]=1.0;      py[1][2]=0.0;		pz[1][2]=0.5;
	px[1][3]=5.0/8.0;  py[1][3]=-5.0/8.0;	pz[1][3]=0.5;
	px[1][4]=-5.0/8.0; py[1][4]=-5.0/8.0;	pz[1][4]=0.5;
	px[1][5]=-1.0;     py[1][5]=0.0;		pz[1][5]=0.5;

	//eyes
	eyex=-1/2.0;eyey=3/8.0;eyez=0.6;
	
	// set the mouth by drawing a triangle face 1
	mouthx[0][0]=-1/2.0; mouthy[0][0]=3/8.0; mouthz[0][0]=0.5;
	mouthx[0][1]=-1.0;   mouthy[0][1]=0.0;   mouthz[0][1]=0.5;
	mouthx[0][2]=-5.0/8.0;mouthy[0][2]=-5.0/8.0; mouthz[0][2]=0.5;

	// set the mouth by drawing a triangle face 2
	mouthx[1][0]=-1/2.0; mouthy[1][0]=3/8.0; mouthz[1][0]=-0.5;
	mouthx[1][1]=-1.0;   mouthy[1][1]=0.0;   mouthz[1][1]=-0.5;
	mouthx[1][2]=-5.0/8.0;mouthy[1][2]=-5.0/8.0; mouthz[1][2]=-0.5;

	// set leg left face 1
	flx[0][0]=1/8.0; fly[0][0]=-5/8.0; flz[0][0]=0.5;
	flx[0][1]=1/8.0; fly[0][1]=-3/2.0; flz[0][1]=0.5;
	flx[0][2]=-0.05; fly[0][2]=-3/2.0; flz[0][2]=0.5;

	// set leg left face 2
	flx[1][0]=1/8.0; fly[1][0]=-5/8.0; flz[1][0]=-0.5;
	flx[1][1]=1/8.0; fly[1][1]=-3/2.0; flz[1][1]=-0.5;
	flx[1][2]=-0.05; fly[1][2]=-3/2.0; flz[1][2]=-0.5;

	// set the leg right face 1
	frx[0][0]=-2/8.0; fry[0][0]=-4/8.0; frz[0][0]=0.5;
	frx[0][1]=-2/8.0; fry[0][1]=-3/2.0; frz[0][1]=0.5;
	frx[0][2]=-3/8.0; fry[0][2]=-3/2.0; frz[0][2]=0.5;

	// set the leg right face 2
	frx[1][0]=-2/8.0; fry[1][0]=-4/8.0; frz[1][0]=-0.5;
	frx[1][1]=-2/8.0; fry[1][1]=-3/2.0; frz[1][1]=-0.5;
	frx[1][2]=-3/8.0; fry[1][2]=-3/2.0; frz[1][2]=-0.5;

	return;
}

void drawPolywoman(float pxp[][6], float pyp[][6], float pzp[][6], float flxp[][3], float flyp[][3], float flzp[][3], float frxp[][3], float fryp[][3],float frzp[][3], float eyex,float eyey,float eyez,float mouthx[][3], float mouthy[][3],float mouthz[][3])
	//this function draws the square icon at the transformed position
{
	int i;
	cout<<"in drawPolywoman"<<endl;

	//draw the eyes
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex3f(eyex,eyey,eyez);
	glEnd();

	for(int face=0;face<2;face++)
	{
		glFrontFace(GL_CW);

		glColor3f(0.9,0.37,0.9);
		glBegin(GL_POLYGON);
		glShadeModel(GL_SMOOTH);
		for(i=0;i<=5;i++)
		{
			glVertex3f(pxp[face][i],pyp[face][i],pzp[face][i]);
		}
	}
glEnd();

	
	//draw the top of the polygon
	glColor3f(0.9,0.0,0.9);
	glBegin(GL_POLYGON);
	glShadeModel(GL_FLAT);	
	glVertex3f(pxp[0][0],pyp[0][0], pzp[0][0]);
	glVertex3f(pxp[0][1],pyp[0][1], pzp[0][1]);
	glVertex3f(pxp[1][1],pyp[1][1], pzp[1][1]);
	glVertex3f(pxp[1][0],pyp[1][0], pzp[1][0]);
	
	glEnd();

	//draw the bottom of the polygon
	glColor3f(0.9,1.0,0.9);
	glBegin(GL_POLYGON);
	glShadeModel(GL_FLAT);	
	glVertex3f(pxp[0][3],pyp[0][3], pzp[0][3]);
	glVertex3f(pxp[0][4],pyp[0][4], pzp[0][4]);
	glVertex3f(pxp[1][4],pyp[1][4], pzp[1][4]);
	glVertex3f(pxp[1][3],pyp[1][3], pzp[1][3]);
	
	glEnd();

	//draw the corner right down of the polygon
	glColor3f(0.9,0.37,0.0);
	glBegin(GL_POLYGON);
	glShadeModel(GL_FLAT);	
	glVertex3f(pxp[0][2],pyp[0][2], pzp[0][2]);
	glVertex3f(pxp[0][3],pyp[0][3], pzp[0][3]);
	glVertex3f(pxp[1][3],pyp[1][3], pzp[1][3]);
	glVertex3f(pxp[1][2],pyp[1][2], pzp[1][2]);
	
	glEnd();

	//draw the corner right up of the polygon
	glColor3f(0.9,0.37,0.0);
	glBegin(GL_POLYGON);
	glShadeModel(GL_FLAT);	
	glVertex3f(pxp[0][1],pyp[0][1], pzp[0][1]);
	glVertex3f(pxp[0][2],pyp[0][2], pzp[0][2]);
	glVertex3f(pxp[1][2],pyp[1][2], pzp[1][2]);
	glVertex3f(pxp[1][1],pyp[1][1], pzp[1][1]);
	
	glEnd();

	//draw the corner left down of the polygon
	glColor3f(0.9,0.37,1.0);
	glBegin(GL_POLYGON);
	glShadeModel(GL_FLAT);	
	glVertex3f(pxp[0][5],pyp[0][5], pzp[0][5]);
	glVertex3f(pxp[0][4],pyp[0][4], pzp[0][4]);
	glVertex3f(pxp[1][4],pyp[1][4], pzp[1][4]);
	glVertex3f(pxp[1][5],pyp[1][5], pzp[1][5]);
	
	glEnd();

	//draw the corner left up of the polygon
	glColor3f(0.9,0.37,1.0);
	glBegin(GL_POLYGON);
	glShadeModel(GL_FLAT);	
	glVertex3f(pxp[0][0],pyp[0][0], pzp[0][0]);
	glVertex3f(pxp[0][5],pyp[0][5], pzp[0][5]);
	glVertex3f(pxp[1][5],pyp[1][5], pzp[1][5]);
	glVertex3f(pxp[1][0],pyp[1][0], pzp[1][0]);
	
	glEnd();

	/// now draws the foot
	//feet right face 1
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(frxp[0][0],fryp[0][0],frzp[0][0]);
	glVertex3f(frxp[0][1],fryp[0][1],frzp[0][1]);
	glVertex3f(frxp[0][2],fryp[0][2],frzp[0][2]);
	glEnd();

	//feet right face 2
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(frxp[1][0],fryp[1][0],frzp[1][0]);
	glVertex3f(frxp[1][1],fryp[1][1],frzp[1][1]);
	glVertex3f(frxp[1][2],fryp[1][2],frzp[1][2]);
	glEnd();

	//feet left face 1
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(flxp[0][0],flyp[0][0],flzp[0][0]);
	glVertex3f(flxp[0][1],flyp[0][1],flzp[0][1]);
	glVertex3f(flxp[0][2],flyp[0][2],flzp[0][2]);
	glEnd();
	//feet left face 2
	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(flxp[1][0],flyp[1][0],flzp[1][0]);
	glVertex3f(flxp[1][1],flyp[1][1],flzp[1][1]);
	glVertex3f(flxp[1][2],flyp[1][2],flzp[1][2]);
	glEnd();

	

	//draw the mouth face 1
	/*glColor3f(0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
	for(int i=0; i<=2;i++)
	{
	glVertex3f(mouthx[0][i],mouthy[0][i],mouthz[0][i]);
	}
	glEnd();
	//draw the mouth face 2
	glColor3f(0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
	for(int i=0; i<=2;i++)
	{
	glVertex3f(mouthx[1][i],mouthy[1][i],mouthz[1][i]);
	}
	glEnd();
	*/
		//draw the mouth
	/*glColor3f(0.0,0.0,0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(mouthx[0],mouthy[0]);
	glVertex2f(mouthx[1],mouthy[1]);
	glVertex2f(mouthx[2],mouthy[2]);
	glEnd();*/

	//now fill the rectangle which is made by half of the square
	//set the shading color to green
	glColor3f(0.5,0.2,0.9);
	glShadeModel(GL_FLAT);
	//redraw the polygon
	/*glBegin(GL_POLYGON);
	//note the colored rectangle must be redraw to render it.
	//first point 
	glVertex3f(pxp[0][0],pyp[0][0],pzp[0][0]);
	//second point
	glVertex3f(pxp[0][1],pyp[0][1],pzp[0][1]);
	//thrid point
	glVertex3f(pxp[0][2],pyp[0][2],pzp[0][2]);
	//forth point
	glVertex3f(pxp[0][3],pyp[0][3],pzp[0][3]);
	//fifth point
	glVertex3f(pxp[0][4],pyp[0][4],pzp[0][4]);
	//sixth point
	glVertex3f(pxp[0][5],pyp[0][5],pzp[0][5]);*/

	//coloring the triangle in black
	/*glColor3f(0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	//redraw the polygon
	glBegin(GL_POLYGON);
	//note the colored rectangle must be redraw to render it.
	//first point 
	glVertex2f(mouthx[0],mouthy[0]);
	//second point
	glVertex2f(mouthx[1],mouthy[1]);
	//thrid point
	glVertex2f(mouthx[2],mouthy[2]);*/
	
	return;

}


//**************************function settrans ******************
void settrans(float t[][3], float scale1,float dx,float dy)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cout<<"in settrans"<<endl;
	glTranslatef(dx,dy,0.0);
	glRotatef(theta,1.0,1.0,1.0);
	
	return;
}

void settransTr(float theta , float dx,float dy,float dz)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cout<<"in settrans"<<endl;
	glTranslatef(dxtr,dytr,dztr);
	glRotatef(thetatr,0.0,1.0,1.0);
}

// Polywoman
void settransPolyWo(float t[][3], float scale1,float dx,float dy)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cout<<"in settrans"<<endl;
	glTranslatef(dxwo,dywo,0.0);
	glRotatef(thetawo,0.0,1.0,0.0);
	return;


}

void settransground(void)// for the ground
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	cout<<"in settrans 2"<<endl;
		return;
}

void drawmouth(float mouthx[], float mouthy[])// draw th trinagle for the mouth
{
	// draw the mouth which is represented by a triangle
	cout<<"in darw mouth"<<endl;
	glColor3f(0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
	for(int i=0; i<3;i++)
	{
	glVertex2f(mouthx[i],mouthy[i]);
	}
	glEnd();

	glColor3f(0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	//redraw the polygon
	glBegin(GL_TRIANGLES);
	//note the colored rectangle must be redraw to render it.
	//first point 
	glVertex2f(mouthx[0],mouthy[0]);
	//second point
	glVertex2f(mouthx[1],mouthy[1]);
	//thrid point
	glVertex2f(mouthx[2],mouthy[2]);
	
}

//********Function Setup RC**********
//Setup the rendering state
void SetupRC(void)
{// this function sets the clear color of an open window and clears the open window
	//set clear color to green
	//glClearColor(0.0,0.0,1.0,1.0);
	glClearColor(0.6f, 0.4f, 0.70f, 1.0f);
	return;
}
//**********FunctionerTimer**********
void TimerFunction(int value)
{static float swc=0.1,sdx=0.1,sdy=0.1;
	//this call back function is call each 30 ms 
	// and changes the location, scale and rotation

	
	switch(frame)
{
	case 1: // frame 1 polyman starts at right and walks to the middle
			theta=0.0;
			dx-=0.10;
			dxwo+=0.05;// polywoman walk from the left to the right
			if(dx<=0.0)
			{
				dx=0.0;
				frame=2;
			}
			if(dxwo>=-2) // she stops before
			{
				dxwo=-1.0;
			}
			break;
	case 2: // frame 2 polyman jumps 
			dy-=0.2;
			
			if(dy<=-4.0)
			{
				dy=-4.0;
				frame=3;
			}
			break;
		
	case 3: // frame 3 polyman rises, and does 360 degree flip
			theta +=8;
			
			dy+=0.2;
			dywo+=0.2;
			if(dywo>-2.5) // polywoman is excited
			{
				dywo=-3.0;
			}
			if(dy>5.0) //polyman rises
			{
				dy=5.0;
				frame=4;
			}
			if(theta>=360.0)//polyman does a 360 degree flip
			{
				frame=4;
				theta=0.0;
			}

			break;
	case 4:    //polyman lands
		
			thetatr +=8;
			dy-=0.2;

			thetawo +=8;

			if(dy<=-4.0)
			{
				dy=-4.0;
				frame=5;
				thetatr+=8;
			}
			if(thetawo>=360)
			{
				thetawo=180,0;
			}
			break;
	case 5:    //polyman stands 

			dy +=0.15;
			dytr -=0.5;
			thetatr +=8;

			if(dy>=-4.0 && dytr<=-0.50)
			{
				dy=-3.0;
				dytr=-0.50;
				frame=6;
				thetatr+=8;
			}

			break;
	case 6: //frame 5 square rolls off stage to left
			dx -=0.13;
			dxwo -=0.13;
			thetatr+=8;
				if(dx<=-8.5)
					{dx=-8.5;
				dxwo=-8.5;
			}
				thetatr+=8;
			break;
}
	

	//Redraw the scene with new coordinates
	glutPostRedisplay();
	glutTimerFunc(30,TimerFunction,1);
}
void ground(void)
{
	glColor3f(0.4,0.5,0.7);
	glShadeModel(GL_FLAT);
	glBegin(GL_LINE_LOOP);
	//Set an axis to represent the ground
	glVertex2f(-6.9,-4.70);//left top
	glVertex2f(6.9,-4.70);//right top
	glVertex2f(6.9,-6.8);//left bottom
	glVertex2f(-6.9,-6.8);//right bottom
	glEnd();
	glColor3f(0.4,0.5,0.7);
	glShadeModel(GL_SMOOTH);
	//redraw the polygon
	glBegin(GL_POLYGON);
	glVertex2f(-6.9,-4.50);//left top
	glVertex2f(6.9,-4.50);//right top
	glVertex2f(6.9,-6.8);//left bottom
	glVertex2f(-6.9,-6.8);//right bottom
	glEnd();

}