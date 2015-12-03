/*
Lionel MUKUNA Ciowela

the polygon have to follow the curve abd performs a back flip 

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
/*This program we have to draw a curve that our polygon have to follow and then at the middle we have to make a back flip and then
polygon have to go ahead untill the point (0,0)

/* declaration of global values
*/
float static theta=0.0, theta2=0.0; // global angular value for rotation of polyman
float scale1=1.0;// global scaling value for square of polyman
float xctrl[11],yctrl[11],uval=0.0; // these are for biezier control points for the path for the cube.
int face=0;int cote=6,frame=1.0;
float dx=7.0,dy=-3.0,dz=0.0;//global movement value for dx and dy of polyman
float x=8.0,y=9.0,z=0.0;

float calcbiezu(float, int , float[]);// calculated biez at apoint u

int fact(int);//calculated factorial

void init(void); // this function to initiliaze the window clear color

void axis(void);
void settransaxis(void);

void RenderScene(void);//this function to draw a square in an opened window
void loadPolyman(float[][7], float[][7],float[][7],float [][3], float [][3],float[][3], float [][3], float [][3],float[][3],float, float,float, float[][3], float[][3],float[][3]); //loads the polyman icon

void drawPolyman(float[][7], float[][7],float[][7],
float[][3],float[][3],float[][3],
float[][3],float[][3],float[][3],
float, float,float, 
float[][3],float[][3],float [][3]);// draws the icon


void settrans( float,float,float); // sets the transformation matrix for desired scale, rotation, new pos

void SetupRC(void);//sets up the clear color
void TimerFunction(int );// thsi call back function is call each 30 ms and changes the location, scale and rotation

// the main program
int main(int argc, char** argv)
{
	char header[]="Biezer by Lionel Mukuna Ciowela";
	glutInit(&argc, argv);// set up the display mode with a single buffer and RGB colors
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
	//Initialize window size and position
	glutInitWindowSize(1016,680);
	glutInitWindowPosition(0,0);
	
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
	float px[2][7],py[2][7],pz[2][7],flx[2][3],fly[2][3],flz[2][3],
		frx[2][3],fry[2][3],frz[2][3],mouthx[2][3], mouthy[2][3],mouthz[2][3];
	
	//xctrl[0]=8.0;yctrl[0]=9.0; // right end point
	//xctrl[1]=7.0;yctrl[1]=8.0;// point 1
	//xctrl[2]=6.0;yctrl[2]=7.0;// point 2
	//xctrl[3]=5.0;yctrl[3]=5.0;// point 3
	//xctrl[4]=2.0;yctrl[4]=6.5;// point 4
	//xctrl[5]=5.0;yctrl[5]=7.0;// point 5
	//xctrl[6]=4.0;yctrl[6]=4.0;
	//xctrl[7]=3.0;yctrl[7]=3.0;
	//xctrl[8]=2.0;yctrl[8]=2.0;
	//xctrl[9]=1.0;yctrl[9]=1.0;
	//xctrl[10]=0.0;yctrl[10]=0.0;// left end point
	xctrl[0]=10.0;yctrl[0]=10.0; // right end point
	xctrl[1]=5.0;yctrl[1]=3.0;// point 1
	xctrl[2]=-6.0;yctrl[2]=10.0;// point 2
	xctrl[3]=8.0;yctrl[3]=11.0;// point 3
	xctrl[4]=3.0;yctrl[4]=10.0;// point 4
	xctrl[5]=0.0;yctrl[5]=0.0;// point 5

	int ncontrolpts=6;

	// Clear the window with the current background color
	cout<<"in renderscene"<<endl;
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// set the viewport to the window dimensions
	glViewport(0,0,558,400);
	
	//Etablish the clipping volumn in user units
	//First clar all tranlsation matricies
	glOrtho(-7.0,11.0,-2.0,11.0,5.0,-5.0);

	//set the current drawing color to black
  glColor3f(0.0,0.0,0.0);
  //set the viewport to the window dimensions
   glViewport(100,100,900,500);

   //  Draw x-axis and y-axis and place tic marks on each
	settransaxis();
   axis();

   // now draw the control points
   glPointSize(5.0);
   glBegin(GL_POINTS);
   for(int i=0;i<ncontrolpts;i++) 
	   glVertex2f(xctrl[i],yctrl[i]);
   glEnd();
   glColor3f(1.0,0.0,0.0);
   glBegin(GL_LINE_STRIP);
  float Uval=0.0;
   for(int i=0;i<=20;i++)
   {
	   glVertex2f(calcbiezu(Uval,5,xctrl),calcbiezu(Uval,5,yctrl));
	   Uval+=0.05;
   }
   glEnd();	
	// set the current drawing color to white

	loadPolyman(px,py,pz,flx,fly,flz,frx,fry,frz,eyex,eyey,eyez,mouthx,mouthy,mouthz);

	//Set the current drawing color to brown
	settrans(scale1, dx,dy);
	//x=dx; y=dy;
	// now draw the square
	drawPolyman(px,py,pz,flx,fly,flz,frx,fry,frz,eyex,eyey,eyez,mouthx,mouthy,mouthz);

	glEnd();
	
	glutSwapBuffers();

	return;
}// end of render scene

//----------Load icon-----------------
void loadPolyman( float px[][7], float py[][7], float pz[][7], float flx[][3], float fly[][3], float flz[][3],float frx[][3],float fry[][3],float frz[][3],float eyex, float eyey,float eyez, float mouthx[][3], float mouthy[][3],float mouthz[][3]
) // this procedure loads a square icon
{
	//set the coordinates of the first polygon
	
	px[0][0]=-5.0/8.0;	py[0][0]=5.0/8.0;	pz[0][0]=-0.5;
	px[0][1]=5.0/8.0;	py[0][1]=5.0/8.0;	pz[0][1]=-0.5;
	px[0][2]=1.0;		py[0][2]=0.0;		pz[0][2]=-0.5;
	px[0][3]=5.0/8.0;	py[0][3]=-5.0/8.0;	pz[0][3]=-0.5;
	px[0][4]=-5.0/8.0;	py[0][4]=-5.0/8.0;	pz[0][4]=-0.5;
	px[0][5]=-1.0;		py[0][5]=0.0;		pz[0][5]=-0.5;
	px[0][6]=-1.0/4.0;	py[0][6]=0.0;		pz[0][6]=-0.5;


	//set the coordinates of the second polygon
	
	px[1][0]=-5.0/8.0; py[1][0]=5.0/8.0;	pz[1][0]=0.5;
	px[1][1]=5.0/8.0;  py[1][1]=5.0/8.0;	pz[1][1]=0.5;
	px[1][2]=1.0;      py[1][2]=0.0;		pz[1][2]=0.5;
	px[1][3]=5.0/8.0;  py[1][3]=-5.0/8.0;	pz[1][3]=0.5;
	px[1][4]=-5.0/8.0; py[1][4]=-5.0/8.0;	pz[1][4]=0.5;
	px[1][5]=-1.0;     py[1][5]=0.0;		pz[1][5]=0.5;
	px[1][6]=-1.0/4.0; py[1][6]=0.0;		pz[1][6]=0.5;

	//eyes
	eyex=-1/2.0;eyey=3/8.0;
	
	// set the mouth by drawing a triangle face 1
	mouthx[0][0]=-1/4.0; mouthy[0][0]=0.0; mouthz[0][0]=-0.5;
	mouthx[0][1]=-1.0;   mouthy[0][1]=0.0;   mouthz[0][1]=-0.5;
	mouthx[0][2]=-5.0/8.0;mouthy[0][2]=-5.0/8.0; mouthz[0][2]=-0.5;

	// set the mouth by drawing a triangle face 2
	mouthx[1][0]=-1/4.0; mouthy[1][0]=0.0; mouthz[1][0]=0.5;
	mouthx[1][1]=-1.0;   mouthy[1][1]=0.0;   mouthz[1][1]=0.5;
	mouthx[1][2]=-5.0/8.0;mouthy[1][2]=-5.0/8.0; mouthz[1][2]=0.5;

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

void drawPolyman(float pxp[][7], float pyp[][7], float pzp[][7], float flxp[][3], float flyp[][3], float flzp[][3], float frxp[][3], float fryp[][3],float frzp[][3], float eyex,float eyey,float eyez,float mouthx[][3], float mouthy[][3],float mouthz[][3])
	//this function draws the square icon at the transformed position
{
	int i;
	cout<<"in drawPolyman"<<endl;

	//draw the eyes
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex3f(eyex,eyey,eyez);
	glEnd();

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex3f(eyex,eyey,0.6);
	glEnd();

	for(face=0;face<2;face++)
	{
		glFrontFace(GL_CW);

		glColor3f(0.5,0.2,0.9);
	// polygon face 1
		glBegin(GL_POLYGON);

		glShadeModel(GL_FLAT);
		for(i=0;i<cote;i++)
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
	glColor3f(0.5,0.2,0.9);
	glBegin(GL_POLYGON);
		
	glVertex3f(pxp[0][5],pyp[0][5], pzp[0][5]);
	glVertex3f(pxp[0][4],pyp[0][4], pzp[0][4]);
	glVertex3f(pxp[1][4],pyp[1][4], pzp[1][4]);
	glVertex3f(pxp[1][5],pyp[1][5], pzp[1][5]);
	
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
	glColor3f(0.6f, 0.4f, 0.70f);
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLES);
	for(int i=0; i<=2;i++)
	{
	glVertex3f(mouthx[0][i],mouthy[0][i],mouthz[0][i]);
	}
	glEnd();

	//draw the mouth face 2
	glColor3f(0.6f, 0.4f, 0.70f);
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLES);
	for(int i=0; i<=2;i++)
	{
	glVertex3f(mouthx[1][i],mouthy[1][i],mouthz[1][i]);
	}
	glEnd();

	
	return;

}

//**************************function settrans ******************
void settrans(float scale1,float dx,float dy)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cout<<"in settrans"<<endl;
	dx=calcbiezu(uval,5,xctrl);
	dy=calcbiezu(uval,5,yctrl);
	x=dx;y=dy;
	//glTranslatef(x,y,z);
	glTranslatef(dx,dy,dz);
	
	glRotatef(theta,0.0,1.0,0.0);
	glRotatef(-theta2,0.0,0.0,1.0);

	return;
}


//********Function Setup RC**********
//Setup the rendering state
void SetupRC(void)
{// this function sets the clear color of an open window and clears the open window
	glClearColor(0.6f, 0.4f, 0.70f, 1.0);
	return;
}
//**********FunctionerTimer**********
void TimerFunction(int value)
{
	static float swc=0.1,sdx=0.1,sdy=0.1;
	//this call back function is call each 30 ms 
	// and changes the location, scale and rotation

			uval+=0.01;
			
			if(uval>=1.0)
			{uval=1.0;
			}

			if(uval>=0.35)
			{
				theta2+=15.0;
			}
			if(uval>=0.6)
			{
				theta2=0.0;
			}

	glutPostRedisplay();
	glutTimerFunc(30,TimerFunction,1);
}

float calcbiezu(float u, int n, float cp[])
{
	float val=0.0;
	for(int i=0;i<=n;i++)
	{
		val+=cp[i]*float(fact(n))/float((fact(i)*fact(n-i)))*pow(u,float(i))*pow(float(1.0-u),float(n-i));
	}
	return val;
}

int fact(int n)
{
	int counter, fct=1;
	if(n==0) return 1;

	for( counter=1;counter<=n;counter++)
	{
		fct=fct*counter;
	}
	return fct;
}

void axis(void)
{
	 glBegin(GL_LINES);
		// Set end points of x-axis
		glVertex2f(-5.0,0.0);//x left
		glVertex2f(10.0,0.0);// x right
		// Now put tic marks on the axis
		for(int x=-1.0;x<=10.0;x+=1.0)
		{glVertex2f(x,0.0);
		 glVertex2f(x,0.5);
		};
		// Set end points of y-axis
		 glVertex2f(0.0,-1.0);// y bottom
		 glVertex2f(0.0,10.0);// y top
		 //Now put tic marks on the axis
		 for(int y=-1.0;y<=10.0;y+=1.0)
		 {glVertex2f(-0.15,y);
		  glVertex2f(0.15,y);
		 };
	glEnd();
}

void settransaxis(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	cout<<"in settrans axis"<<endl;
		return;
}