/*********************** 3D Car Driving Game***************************************/
/**************************************************************/
/*                               Baki MD. Noor Uddin                                                                */
/*                                Pabna University of Science & Technology                          */
/*                                 Roll: 150117                                                                              */
/*                                 github.com/MDNoorUddin                                                     */
/**************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include <windows.h>
#include <GL/glut.h>
#include<vector>
using namespace std;
#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

double map_angle;
double Block_size=40;
double Block_distance=38,size_cube=38;
int slices_spehere=30, stacks_spehere=30;
int segments_cylinder=24;
double temp=0;
double move_pos=2;
double ar=0;
double car=0;
double X=10,Y=40,Z=10;
double leftRightMove=0;
double sky=-1000;

vector< pair<int,pair<int,int> > > CARS;
int NumberOfCar;

struct point
{
	double x,y,z;
};

point l,u,r,pos;
void drive()
{
	for(int i=200;i<=40000;i+=200)
	{
        int I = rand()%1000;
        int J = rand()%30;
        int K = rand()%2;
		CARS.push_back( make_pair(K,make_pair(I+i,J) ) );
	}
}

void otherCar()
{
    glPushMatrix();
        {
          glColor3f(.3,.8,1);
          glScalef(2,1,.4);    /*******lower part********/
          glutSolidCube(10);
        }glPopMatrix();

        glPushMatrix();
        {
           glTranslatef(0,0,3);
           glColor3f(.45,.56,.67);   /******* upper part********/
           glScalef(1,1,.6);
           glutSolidCube(10);
        }glPopMatrix();

        glPushMatrix();
       {
          glTranslatef(4,5,-2);
          glColor3f(0,0,1);   /******* front wheel left part********/
          glScalef(2,.7,1);
          glutSolidSphere(2,100,100);
        }glPopMatrix();


       glPushMatrix();
       {
          glTranslatef(-4,5,-2);
          glColor3f(0,0,1);   /******* front wheel right part********/
          glScalef(1,.7,1);
          glutSolidSphere(2,100,100);
      }glPopMatrix();

      glPushMatrix();
      {
         glTranslatef(4,-5,-2);
         glColor3f(0,0,1);   /******* behind wheel left part********/
         glScalef(1,.7,1);
         glutSolidSphere(2,100,100);
      }glPopMatrix();


      glPushMatrix();
      {
         glTranslatef(-4,-5,-2);
         glColor3f(0,0,1);   /******* behind wheel right part********/
         glScalef(1,.7,1);
         glutSolidSphere(2,100,100);
      }glPopMatrix();
}

void boat()
{
    glColor3f(.678,.23,.4);
    glPushMatrix();

       glBegin(GL_POLYGON);

          glVertex3f(15,0,5);
          glVertex3f(-15,0,5);
          glVertex3f(-15,0,0);
          glVertex3f(15,0,0);

 glEnd();

    glPopMatrix();

    glPushMatrix();

       glBegin(GL_POLYGON);

          glVertex3f(30,0,0);
          glVertex3f(-30,0,0);
          glVertex3f(-10,0,-8);
          glVertex3f(10,0,-8);
           glEnd();

    glPopMatrix();

}
void drawRoad()
{
    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,0,-30);
        glVertex3f(-100,0,-30);

        glVertex3f(-100,-5000,-30);
        glVertex3f(100,-5000,-30);

      glEnd();

    glPopMatrix();
}

void drawRoadMiddle()
{

    glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,0,-30);
        glVertex3f(2,0,-30);

        glVertex3f(-2,-5000,-30);
        glVertex3f(2,-5000,-30);

      glEnd();

    glPopMatrix();
}

void sideRoad()
{
    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,0,-30);
        glVertex3f(-100,0,-30);

        glVertex3f(-100,-300,-30);
        glVertex3f(100,-300,-30);

      glEnd();

    glPopMatrix();
}

void drawMainCar()
{
    glPushMatrix();
    cout<<car<<endl;


    glTranslatef(leftRightMove,car,0);
    glRotatef(90,0,0,1);

    glPushMatrix();
    {
        glColor3f(1,.8,3);
        glScalef(2,1,.4);    /*******lower part********/
         glutSolidCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0,0,3);
        glColor3f(.67,.67,.67);   /******* upper part********/
        glScalef(1,1,.6);
         glutSolidCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(4,5,-2);
        glColor3f(1,.3,8);   /******* front wheel left part********/
        glScalef(2,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();


    glPushMatrix();
    {
        glTranslatef(-4,5,-2);
        glColor3f(1,0,1);   /******* front wheel right part********/
        glScalef(1,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(4,-5,-2);
        glColor3f(1,.6,8);   /******* behind wheel left part********/
        glScalef(1,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();


    glPushMatrix();
    {
        glTranslatef(-4,-5,-2);
        glColor3f(1,.3,8);   /******* behind wheel right part********/
        glScalef(1,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();

    glPopMatrix();
}

void drawBackground()
{
    glPushMatrix();
    glTranslatef(0,sky,500);
    glRotatef(90,0,0,1);
    glColor3f(.3,0.9,.9);

    glScalef(.003,2,1);
    glutSolidCube(1000);

    glPopMatrix();

}

void drawHill()
{

    glPushMatrix();
      glTranslatef(-500,sky,440);
      glColor3f(.757,.4,0);
      glutSolidSphere(120,20,20);
    glPopMatrix();
    glColor3f(0,0.9,0.5);
    glPushMatrix();
    glTranslatef(500,sky+30,0);
    glRotatef(90,0,0,1);
    glutSolidCone(200,400,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(700,sky+30,0);
    glRotatef(90,0,0,1);
    glutSolidCone(200,400,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300,sky+30,0);
    glRotatef(90,0,0,1);
    glutSolidCone(200,400,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-500,sky+30,0);
    glRotatef(90,0,0,1);
    glColor3f(0,0.9,0.5);
    glutSolidCone(200,400,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-700,sky+30,0);
    glRotatef(90,0,0,1);
    glColor3f(0,0.9,0.5);
    glutSolidCone(200,400,20,20);
    glPopMatrix();

}

void drawTent()
{

            glPushMatrix();
            {
               glTranslatef(0,0,0);
               glColor3f(.6,.6,.6);
               glRotatef(90,1,0,0);
               glutSolidCube(50);
            }glPopMatrix();





            glPushMatrix();
            {
               glTranslatef(0,0,20);
               glColor3f(1,.6,0);
              //glRotatef(90,1,0,0);
              glutSolidCone(40,30,30,40);
             }glPopMatrix();
}

void talgas()
{

               glPushMatrix();
                glColor3f(.5,.5,.3);
                glScalef(.01,.4,5);
                glutSolidSphere(7,10,10);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(5,0,1);
                glColor3f(0,.5,.3);
                glutSolidSphere(10,10,10);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(-5,0,1);
                glColor3f(0,.5,.3);
                glutSolidSphere(10,10,10);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0,0,20);
                glColor3f(0,.5,.2);
                glutSolidSphere(15,10,10);
                glPopMatrix();
}

void Signboard()
{
             glPushMatrix();
             glColor3f(0,1,0);
             glutSolidCone(20,30,20,20);

             glPopMatrix();

             glPushMatrix();
             glColor3f(.5,.5,.3);
             glScalef(.01,.4,5);
             glutSolidSphere(7,10,10);

             glPopMatrix();

}

void Naricalgas()
{
    glPushMatrix();

               glTranslatef(0,0,30);
               glRotatef(45,0,1,0);
               glColor3f(0,.674,.543);
               glScalef(.5,1,5);
               glutSolidSphere(4,10,10);

              glPopMatrix();

              glPushMatrix();

              glTranslatef(0,0,30);
              glRotatef(315,0,1,0);
              glColor3f(0,.674,.543);
              glScalef(.5,1,5);
              glutSolidSphere(4,10,10);

              glPopMatrix();

              glPushMatrix();

              glTranslatef(0,0,30);

              glColor3f(0,.674,.543);

              glScalef(.5,1,5);

              glutSolidSphere(4,10,10);

             glPopMatrix();



             glPushMatrix();

             glTranslatef(0,0,0);

             glPushMatrix();

             glPushMatrix();
             glColor3f(.5,.5,.3);
             glScalef(.01,.4,5);
             glutSolidSphere(7,10,10);

            glPopMatrix();
}

void city()
{

    glPushMatrix();

       glColor3f(.789,.299,.8);  //main building
       glScalef(1.8,1,5);
       glutSolidCube(20);


     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,0);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,0);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,20);
        glutSolidCube(10);
     glPopMatrix();

     /***********************************/

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,40);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,40);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,-20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,-20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,-40);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,-40);
        glutSolidCube(10);
     glPopMatrix();


      glTranslatef(40,0,-20);


      glPushMatrix();

       glColor3f(.334,.789,.8);  //main building
       glScalef(1.8,1,5);
       glutSolidCube(20);


     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,0);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,0);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,20);
        glutSolidCube(10);
     glPopMatrix();

     /***********************************/

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,40);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,40);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,-20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,-20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,-40);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,-40);
        glutSolidCube(10);
     glPopMatrix();

     /**********************************************************************/

     glTranslatef(-120,0,0);


      glPushMatrix();

       glColor3f(.789,.567,.3);  //main building
       glScalef(2.5,1,3);
       glutSolidCube(20);


     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,0);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,0);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,20);
        glutSolidCube(10);
     glPopMatrix();

     /***********************************/
     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,-20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,-20);
        glutSolidCube(10);
     glPopMatrix();


     glTranslatef(-40,0,0);
     glPushMatrix();

       glColor3f(.9,.9,.3);  //main building
       glScalef(1.3,1,8);
       glutSolidCube(20);


     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,0);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,0);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,60);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,40);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,40);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,60);
        glutSolidCube(10);
     glPopMatrix();

     /***********************************/
     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,-20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,-20);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,-60);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,-40);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(-10,7,-40);
        glutSolidCube(10);
     glPopMatrix();

     glPushMatrix();
        glColor3f(.9,.9,.9);
        glTranslatef(10,7,-60);
        glutSolidCube(10);
     glPopMatrix();

}

void river()
{
    glPushMatrix();
    glColor3f(0.09, 0.5, 0.689);
      glTranslated(0,0,-40);
      glBegin(GL_POLYGON);

        glVertex3f(700,0,0);
        glVertex3f(-700,0,0);

        glVertex3f(-700,-3000,0);
        glVertex3f(700,-3000,0);

      glEnd();

    glPopMatrix();

}

void display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.345, 0.4, 0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();


	gluLookAt(0,Y,Z,	0,-40000,0,	0,0,1);

	glMatrixMode(GL_MODELVIEW);



    if(abs(car)<=4000)
    {
        car-=1;
        Y-=1;
        sky-=1;
        int j=0;
        for(int i=1;i<=100;i++,j+=40){

            glPushMatrix();
               glTranslatef(-120,-j,0);
               //glRotatef(270,0,0,1);
                if(i<=33)
                Naricalgas();
                else if(i<=66)
                    talgas();
                else
                    Signboard();
            glPopMatrix();

         }

         j+=200;

         for(int i=1;i<=5;i++,j+=200)
         {
             glPushMatrix();
               glTranslatef(-120,-j,0);
               glRotatef(270,0,0,1);
                city();
            glPopMatrix();
         }
         j=0;
       for(int i=1;i<=100;i++,j+=40){
            glPushMatrix();
               glTranslatef(120,-j,0);
               //glRotatef(20,0,0,1);
                if(i<=33)
                Naricalgas();
                else if(i<=66)
                    talgas();
                else
                    Signboard();
            glPopMatrix();

        }

        j+=200;

        for(int i=1;i<=5;i++,j+=200)
         {
             glPushMatrix();
               glTranslatef(120,-j,0);
               glRotatef(90,0,0,1);
                city();
            glPopMatrix();
         }

    drawRoad();

    drawRoadMiddle();

    }

    else if(abs(car)<=8000)
    {
        car-=2;
        Y-=2;
        sky-=2;
        for(int i=0,j=4000;i<=20;i++,j+=200){

                glPushMatrix();

                glTranslatef(-120,-j,0);
                glRotated(270,0,0,1);

                city();

                glPopMatrix();
        }
       for(int i=0,j=4000;i<=20;i++,j+=200){

             glPushMatrix();

                glTranslatef(120,-j,0);
                glRotated(90,0,0,1);

                city();

                glPopMatrix();
       }

    glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-4000,-30);
        glVertex3f(2,-4000,-30);

        glVertex3f(-2,-9500,-30);
        glVertex3f(2,-9500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-4000,-30);
        glVertex3f(-100,-4000,-30);

        glVertex3f(-100,-9500,-30);
        glVertex3f(100,-9500,-30);

      glEnd();

    glPopMatrix();


    }

    else if(abs(car)<=12000)
    {

       car-=3;
       Y-=3;
       sky-=3;
        for(int i=1,j=8000;i<=5;i++,j+=200)
        {
            glPushMatrix();
             glTranslatef(-120,-j,0);
            if(i%3==0)
            {
                Naricalgas();

            }
            else if(i%1==0)
            {
                talgas();
            }
            else
            {
                Signboard();

            }
            glPopMatrix();
        }

        for(int i=1,j=8000;i<=5;i++,j+=200)
        {
            glPushMatrix();
             glTranslatef(120,-j,0);
            if(i%3==0)
            {
                Naricalgas();

            }
            else if(i%1==0)
            {
                talgas();
            }
            else
            {
                Signboard();

            }
            glPopMatrix();
        }
        for(int i=1,j=12000;i<=5;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(120,-j,0);

            if(i<=10)
            {
                drawTent();

            }
            else
            {
                Naricalgas();
            }

            glPopMatrix();

        }

        for(int i=1,j=12000;i<=5;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(-120,-j,0);

            if(i<=10)
            {
                talgas();

            }
            else
            {
                drawTent();
            }

            glPopMatrix();

        }
         glPushMatrix();
            glTranslatef(0,-9000,0);
            river();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(120,-9400,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-120,-9500,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-150,-9700,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(150,-10000,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-100,-9100,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(100,-9100,0);
            boat();
        glPopMatrix();


        glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-8000,-30);
        glVertex3f(2,-8000,-30);

        glVertex3f(-2,-13500,-30);
        glVertex3f(2,-13500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-8000,-30);
        glVertex3f(-100,-8000,-30);

        glVertex3f(-100,-13500,-30);
        glVertex3f(100,-13500,-30);

      glEnd();

    glPopMatrix();

    }

    else if(abs(car)<=16000)
    {
        car-=4;
        Y-=4;
        sky-=4;

        for(int i=1,j=12000;i<=20;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(120,-j,0);

            if(i<=10)
            {
                drawTent();

            }
            else
            {
                Naricalgas();
            }

            glPopMatrix();

        }

        for(int i=1,j=12000;i<=20;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(-120,-j,0);

            if(i<=10)
            {
                talgas();

            }
            else
            {
                drawTent();
            }

            glPopMatrix();

        }


        glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-12000,-30);
        glVertex3f(2,-12000,-30);

        glVertex3f(-2,-17500,-30);
        glVertex3f(2,-17500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-12000,-30);
        glVertex3f(-100,-12000,-30);

        glVertex3f(-100,-17500,-30);
        glVertex3f(100,-17500,-30);

      glEnd();

    glPopMatrix();

    }

    else if(abs(car)<=20000)
    {
        car-=5;
        Y-=5;
        sky-=5;
        for(int i=1,j=16000;i<=20;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(120,-j,0);

            if(i%3==0)
                Naricalgas();
            else if(i%3==1)
                talgas();
            else
                Signboard();
            glPopMatrix();

        }

        for(int i=1,j=16000;i<=20;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(-120,-j,0);

            if(i%3==0)
                Naricalgas();
            else if(i%3==1)
                talgas();
            else
                Signboard();

            glPopMatrix();

        }


        glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-16000,-30);
        glVertex3f(2,-16000,-30);

        glVertex3f(-2,-21500,-30);
        glVertex3f(2,-21500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-16000,-30);
        glVertex3f(-100,-16000,-30);

        glVertex3f(-100,-21500,-30);
        glVertex3f(100,-21500,-30);

      glEnd();

    glPopMatrix();
    }

    else if(abs(car)<=24000)
    {
        car-=6;
        Y-=6;
        sky-=6;
        for(int i=1,j=20000;i<=5;i++,j+=200)
        {
            glPushMatrix();
             glTranslatef(-120,-j,0);
            if(i%3==0)
            {
                Naricalgas();

            }
            else if(i%1==0)
            {
                talgas();
            }
            else
            {
                Signboard();

            }
            glPopMatrix();
        }

        for(int i=1,j=20000;i<=5;i++,j+=200)
        {
            glPushMatrix();
             glTranslatef(120,-j,0);
            if(i%3==0)
            {
                Naricalgas();

            }
            else if(i%1==0)
            {
                talgas();
            }
            else
            {
                Signboard();

            }
            glPopMatrix();
        }

         glPushMatrix();
            glTranslatef(0,-21000,0);
            river();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(120,-21400,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-120,-21500,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-150,-21700,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(150,-22000,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-100,-21100,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(100,-21100,0);
            boat();
        glPopMatrix();


        glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-20000,-30);
        glVertex3f(2,-20000,-30);

        glVertex3f(-2,-30000,-30);
        glVertex3f(2,-30000,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-20000,-30);
        glVertex3f(-100,-20000,-30);

        glVertex3f(-100,-30000,-30);
        glVertex3f(100,-30000,-30);

      glEnd();

    glPopMatrix();
    }

    else if(abs(car)<=28000)
    {
        car-=7;
        Y-=7;
        sky-=7;
        for(int i=0,j=24000;i<=20;i++,j+=200){

                glPushMatrix();

                glTranslatef(-120,-j,0);
                glRotated(270,0,0,1);

                city();

                glPopMatrix();
        }
       for(int i=0,j=24000;i<=20;i++,j+=200){

             glPushMatrix();

                glTranslatef(120,-j,0);
                glRotated(90,0,0,1);

                city();

                glPopMatrix();
       }

    glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-24000,-30);
        glVertex3f(2,-4000,-30);

        glVertex3f(-2,-31500,-30);
        glVertex3f(2,-31500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-24000,-30);
        glVertex3f(-100,-24000,-30);

        glVertex3f(-100,-31500,-30);
        glVertex3f(100,-31500,-30);

      glEnd();

    glPopMatrix();


    }

    else if(abs(car)<=32000)
    {
        car-=8;
        Y-=8;
        sky-=8;
        int j=28000;
        for(int i=1;i<=100;i++,j+=40){

            glPushMatrix();
               glTranslatef(-120,-j,0);
               //glRotatef(270,0,0,1);
                if(i<=33)
                Naricalgas();
                else if(i<=66)
                    talgas();
                else
                    Signboard();
            glPopMatrix();

         }

         j+=200;

         for(int i=1;i<=5;i++,j+=200)
         {
             glPushMatrix();
               glTranslatef(-120,-j,0);
               glRotatef(270,0,0,1);
                city();
            glPopMatrix();
         }
         j=28000;
       for(int i=1;i<=100;i++,j+=40){
            glPushMatrix();
               glTranslatef(120,-j,0);
               //glRotatef(20,0,0,1);
                if(i<=33)
                Naricalgas();
                else if(i<=66)
                    talgas();
                else
                    Signboard();
            glPopMatrix();

        }

        j+=200;

        for(int i=1;i<=5;i++,j+=200)
         {
             glPushMatrix();
               glTranslatef(120,-j,0);
               glRotatef(90,0,0,1);
                city();
            glPopMatrix();
         }

         glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-28000,-30);
        glVertex3f(2,-28000,-30);

        glVertex3f(-2,-33500,-30);
        glVertex3f(2,-33500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-28000,-30);
        glVertex3f(-100,-28000,-30);

        glVertex3f(-100,-33500,-30);
        glVertex3f(100,-33500,-30);

      glEnd();

    glPopMatrix();

    }

    else if(abs(car)<=36000)
    {
        car-=9;
        Y-=9;
        sky-=9;
        for(int i=0,j=32000;i<=20;i++,j+=200){

                glPushMatrix();

                glTranslatef(-120,-j,0);
                glRotated(270,0,0,1);

                city();

                glPopMatrix();
        }
       for(int i=0,j=32000;i<=20;i++,j+=200){

             glPushMatrix();

                glTranslatef(120,-j,0);
                glRotated(90,0,0,1);

                city();

                glPopMatrix();
       }

    glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-32000,-30);
        glVertex3f(2,-32000,-30);

        glVertex3f(-2,-37500,-30);
        glVertex3f(2,-37500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-32000,-30);
        glVertex3f(-100,-32000,-30);

        glVertex3f(-100,-37500,-30);
        glVertex3f(100,-37500,-30);

      glEnd();

    glPopMatrix();


    }

    else if(abs(car)<=40000)
    {
        car-=10;
        Y-=10;
        sky-=10;

        for(int i=1,j=36000;i<=5;i++,j+=200)
        {
            glPushMatrix();
             glTranslatef(-120,-j,0);
            if(i%3==0)
            {
                Naricalgas();

            }
            else if(i%1==0)
            {
                talgas();
            }
            else
            {
                Signboard();

            }
            glPopMatrix();
        }

        for(int i=1,j=36000;i<=5;i++,j+=200)
        {
            glPushMatrix();
             glTranslatef(120,-j,0);
            if(i%3==0)
            {
                Naricalgas();

            }
            else if(i%1==0)
            {
                talgas();
            }
            else
            {
                Signboard();

            }
            glPopMatrix();
        }
        for(int i=1,j=40000;i<=5;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(120,-j,0);

            if(i<=10)
            {
                drawTent();

            }
            else
            {
                Naricalgas();
            }

            glPopMatrix();

        }

        for(int i=1,j=40000;i<=5;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(-120,-j,0);

            if(i<=10)
            {
                talgas();

            }
            else
            {
                drawTent();
            }

            glPopMatrix();

        }
         glPushMatrix();
            glTranslatef(0,-37000,0);
            river();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(120,-37400,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-120,-37500,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-150,-37700,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(150,-38000,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-100,-37100,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(100,-37100,0);
            boat();
        glPopMatrix();


        glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-36000,-30);
        glVertex3f(2,-36000,-30);

        glVertex3f(-2,-41500,-30);
        glVertex3f(2,-41500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-36000,-30);
        glVertex3f(-100,-36000,-30);

        glVertex3f(-100,-41500,-30);
        glVertex3f(100,-41500,-30);

      glEnd();

    glPopMatrix();

    }

    else if(abs(car)<=44000)
    {
        car-=11;
        Y-=11;
        sky-=11;

        for(int i=1,j=40000;i<=20;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(120,-j,0);

            if(i<=10)
            {
                drawTent();

            }
            else
            {
                Naricalgas();
            }

            glPopMatrix();

        }

        for(int i=1,j=40000;i<=20;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(-120,-j,0);

            if(i<=10)
            {
                talgas();

            }
            else
            {
                drawTent();
            }

            glPopMatrix();

        }


        glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-40000,-30);
        glVertex3f(2,-40000,-30);

        glVertex3f(-2,-45500,-30);
        glVertex3f(2,-45500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-40000,-30);
        glVertex3f(-100,-40000,-30);

        glVertex3f(-100,-45500,-30);
        glVertex3f(100,-45500,-30);

      glEnd();

    glPopMatrix();

    }

    else if(abs(car)<=48000)
    {
        car-=12;
        Y-=12;
        sky-=12;
        for(int i=1,j=44000;i<=20;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(120,-j,0);

            if(i%3==0)
                Naricalgas();
            else if(i%3==1)
                talgas();
            else
                Signboard();
            glPopMatrix();

        }

        for(int i=1,j=44000;i<=20;i++,j+=200)
        {
            glPushMatrix();

            glTranslatef(-120,-j,0);

            if(i%3==0)
                Naricalgas();
            else if(i%3==1)
                talgas();
            else
                Signboard();

            glPopMatrix();

        }


        glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-44000,-30);
        glVertex3f(2,-44000,-30);

        glVertex3f(-2,-49500,-30);
        glVertex3f(2,-49500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-44000,-30);
        glVertex3f(-100,-44000,-30);

        glVertex3f(-100,-49500,-30);
        glVertex3f(100,-49500,-30);

      glEnd();

    glPopMatrix();
    }

    else if(abs(car)<=52000)
    {
        car-=13;
        Y-=13;
        sky-=13;
        for(int i=1,j=48000;i<=5;i++,j+=200)
        {
            glPushMatrix();
             glTranslatef(-120,-j,0);
            if(i%3==0)
            {
                Naricalgas();

            }
            else if(i%1==0)
            {
                talgas();
            }
            else
            {
                Signboard();

            }
            glPopMatrix();
        }

        for(int i=1,j=48000;i<=5;i++,j+=200)
        {
            glPushMatrix();
             glTranslatef(120,-j,0);
            if(i%3==0)
            {
                Naricalgas();

            }
            else if(i%1==0)
            {
                talgas();
            }
            else
            {
                Signboard();

            }
            glPopMatrix();
        }

         glPushMatrix();
            glTranslatef(0,-49000,0);
            river();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(120,-49400,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-120,-50500,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-150,-51700,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(150,-52000,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-100,-511100,0);
            boat();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(100,-51100,0);
            boat();
        glPopMatrix();


        glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-48000,-30);
        glVertex3f(2,-48000,-30);

        glVertex3f(-2,-53500,-30);
        glVertex3f(2,-53500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-48000,-30);
        glVertex3f(-100,-48000,-30);

        glVertex3f(-100,-53500,-30);
        glVertex3f(100,-53500,-30);

      glEnd();

    glPopMatrix();
    }

    else if(abs(car)<=56000)
    {
        car-=14;
        Y-=14;
        sky-=14;
        for(int i=0,j=52000;i<=20;i++,j+=200){

                glPushMatrix();

                glTranslatef(-120,-j,0);
                glRotated(270,0,0,1);

                city();

                glPopMatrix();
        }
       for(int i=0,j=52000;i<=20;i++,j+=200){

             glPushMatrix();

                glTranslatef(120,-j,0);
                glRotated(90,0,0,1);

                city();

                glPopMatrix();
       }

    glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,-52000,-30);
        glVertex3f(2,-52000,-30);

        glVertex3f(-2,-57500,-30);
        glVertex3f(2,-57500,-30);

      glEnd();

    glPopMatrix();


    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,-52000,-30);
        glVertex3f(-100,-52000,-30);

        glVertex3f(-100,-56500,-30);
        glVertex3f(100,-56500,-30);

      glEnd();

    glPopMatrix();


    }
    cout<<leftRightMove<<"------\n";
    drawMainCar();

    /*********************************************************/
    int II=0;
    int Len=CARS.size();
    for(int I=NumberOfCar;I<Len;I++){

        if(CARS[I].second.first-abs(car)>=700)
        {
            break;
        }

        if(abs(car)>CARS[I].second.first+700)
        {
            NumberOfCar++;
        }
        else{
          glPushMatrix();
          if(CARS[I].first==0)
           glTranslatef(CARS[I].second.second,-CARS[I].second.first++,0);
          else
           glTranslatef(-CARS[I].second.second,-CARS[I].second.first++,0);
           glRotatef(90,0,0,1);
           glColor3f(1,0,0);
           otherCar();
           glPopMatrix();
        }
  }

/*********************************************************************************************/
    for(int I=0;I<Len;I++){

         if(CARS[I].first==0 && car-20<=-CARS[I].second.first &&car>=-CARS[I].second.first-20 && leftRightMove >=CARS[I].second.second-10 && leftRightMove <= CARS[I].second.second+10)
         {
            exit(0);
         }

          else if(CARS[I].first==1 && car-20<=-CARS[I].second.first &&car>=-CARS[I].second.first-20 && leftRightMove <=-CARS[I].second.second+10 && leftRightMove >= -CARS[I].second.second-10)
         {
            exit(0);
         }

     }

    drawBackground();

    drawHill();

	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}
void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;

	u.x=0;
    u.y=0;
    u.z=1;


    r.x=-1/sqrt(2);
    r.y=1/sqrt(2);
    r.z=0;

    l.x=-1/sqrt(2) ;
    l.y=-1/sqrt(2) ;
    l.z=0;

    pos.x=100;
    pos.y=100;
    pos.z=0;


	map_angle=90;

	glClearColor(0,0,0,0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(80,	1,	1,	70000.0);

}
void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraHeight -= 3.0;
			car-=1000;
			Y-=1000;
			X-=3;
            sky-=1000;
			if(Y==-10000){
                Y=50;car=0;sky=-1000;
			}
			pos.x-=l.x*move_pos;
			pos.y-=l.y*move_pos;
			pos.z-=l.z*move_pos;

			break;
		case GLUT_KEY_UP:		// up arrow key
			//cameraHeight += 3.0;
			car-=10;
			Y-=10;
			X-=3;
            sky-=10;
			if(Y==-20000){
                Y=50;car=0;sky=-1000;
			}
			pos.x+=l.x*move_pos;
			pos.y+=l.y*move_pos;
			pos.z+=l.z*move_pos;
			break;

		case GLUT_KEY_RIGHT:
               if(leftRightMove>=-30){
               leftRightMove-=5;
		       car-=5;
			   Y-=5;
			   sky-=5;
            }
			cameraAngle += 0.03;
			pos.x+=r.x*move_pos;
			pos.y+=r.y*move_pos;
			pos.z+=r.z*move_pos;
			break;
		case GLUT_KEY_LEFT:
            if(leftRightMove<=30){
		    leftRightMove+=5;
		    car-=5;
			Y-=5;
			sky-=5;
        }
			cameraAngle -= 0.03;
			pos.x-=r.x*move_pos;
			pos.y-=r.y*move_pos;
			pos.z-=r.z*move_pos;

			break;

		case GLUT_KEY_PAGE_UP:
		    Z+=10;
			break;
		case GLUT_KEY_PAGE_DOWN:
            Z-=10;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
		    Y+=10;
			break;
		case GLUT_KEY_END:
            Y-=10;
			break;

		default:
			break;
	}
}


int main(int argc, char **argv){
	drive();
	glutInit(&argc,argv);
	glutInitWindowSize(500, 900);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("3D Car Driving Game");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

//	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	//glutMouseFunc(mouseListener);
	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
