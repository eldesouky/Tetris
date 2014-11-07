//
//  main.cpp
//  DosTetris
//
//  Created by Mahmoud Eldesouky on 10/14/14.
//  Copyright (c) 2014 Mahmoud Eldesouky. All rights reserved.
//
#include "square.h"
#include "square.cpp"
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

void Display(void);
void Display1(void);
void MyKeyboard(unsigned char,int,int);
int maxheight(int);
bool isEnd();
void animate(void);
bool leftx (int ,int );
bool rightx (int ,int );
int yrange(int);
void scoreC();
void removey(int y);

square * shapes_intialization();
square * s1_int();
square * s2_int();
square * s3_int();
square * s4_int();
square * s5_int();
square * s6_int();
square * s7_int();

double x1_hy; double x2_hy;
double x3_hy; double x4_hy;
double hy;

double x1 ; double x2;
double x3 ; double x4;
double y1; double y2;
double y3; double y4;

int pshape=1;
int cshape;
static int fshape=1;
static int pfshape=1;
static bool genrate=true;
static bool genrate1=false;
int yremove;

int start=0;                        //739  / \     // tetris center => 250
int i=0;                            //685   |
int count =0;                       //631   |
int score=0;                        //577   |
int shape;                          //523   |
bool shoot=true;                    //469   |
bool begin=true;                    //415   |
bool end =false;                    //361   |
bool endgame=false;

////Shape 1          ////Shape 2            ////Shape3          ////Shape4          ////Shape5
double s1_x1=177;    double s2_x1=225;      double s3_x1=225;   double s4_x1=225;   double s5_x1=273;
double s1_x2=225;    double s2_x2=273;      double s3_x2=273;   double s4_x2=225;   double s5_x2=225;
double s1_x3=273;    double s2_x3=225;      double s3_x3=321;   double s4_x3=273;   double s5_x3=321;
double s1_x4=321;    double s2_x4=321;      double s3_x4=321;   double s4_x4=273;   double s5_x4=273;
double s1_y=739;     double s2_y1=685;      double s3_y1=685;   double s4_y1=739;   double s5_y1=739;
                     double s2_y2=685;      double s3_y2=685;   double s4_y2=685;   double s5_y2=685;
                     double s2_y3=739;      double s3_y3=739;   double s4_y3=739;   double s5_y3=739;
                     double s2_y4=685;      double s3_y4=685;   double s4_y4=685;   double s5_y4=685;

////Shape 6          ////Shape 7
double s6_x1=225;    double s7_x1=225;
double s6_x2=273;    double s7_x2=273;
double s6_x3=273;    double s7_x3=273;
double s6_x4=321;    double s7_x4=321;
double s6_y1=685;    double s7_y1=739;
double s6_y2=685;    double s7_y2=685;
double s6_y3=739;    double s7_y3=739;
double s6_y4=685;    double s7_y4=685;

double r; double g; double b;
double r1; double g1; double b1;
double xold;
double yold;


square points [140];
square *new_points;


int main(int argc,char** argr)
{
	glutInit(&argc,argr);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500.0f,768.0f);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Testing");
    glutDisplayFunc(Display);
    glutKeyboardFunc(MyKeyboard);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glPointSize(46.0);
	glLineWidth(2.0);
	gluOrtho2D(0.0,500.0,0.0,768.0);
	glutMainLoop();
    return 0;
}
void print(int x, int y, char *string)
{
    int len, i;
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
    }
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    scoreC();
    glColor3f(01.0,0,0);
    char * stC[100];
    sprintf((char *)stC,"Score: %d",score );
    print(0,740,(char *)stC);
    glBegin(GL_LINES);
    glColor3f(1.0f,1.0f,1.0f);
    
    glVertex3f(10.0f, 10.0f, 0.0f);
    glVertex3f(10.0f, 740.0f, 0.0f);
    
    glVertex3f(490, 740.0f, 0.0f);
    glVertex3f(490, 10.0f, 0.0f);
    
    glVertex3f(490, 10.0f, 0.0f);
    glVertex3f(10.0f, 10.0f, 0.0f);
    glEnd( );
    
   if (start==1) {
    
    if (endgame) {
        glColor3f(01.0,0,0);
        char * stC[12];
        sprintf((char *)stC,"Game Over");
        print(200,450,(char *)stC);
        char * stC1[12];
        sprintf((char *)stC1,"Score: %d",score );
        print(210,430,(char *)stC1);
        glPopMatrix();
        glFlush();
        return;
    }
  if (!end) {
    if (count != 0) {
    for (int j=0; j < count;j++) {
        glBegin(GL_POINTS);
        r1=(double)points[j].r;
        g1=(double)points[j].g;
        b1=(double)points[j].b;
        xold=(double)points[j].x;
        yold=(double)points[j].y;
        glColor3f(r1,g1,b1);
        if (xold != NULL || yold!= NULL) {
               glVertex3f(xold, yold, 0);
        }
     
        glEnd();
    }
    }
    if (shoot== true) {
        
        // add the random shape intialization code
     //new_points = s4_int();
     new_points = shapes_intialization();
        shoot = false;
         x1 =new_points[0].x; x2=new_points[1].x;
         x3 =new_points[2].x; x4=new_points[3].x;
         y1=new_points[0].y;  y2=new_points[1].y;
         y3=new_points[2].y;  y4=new_points[3].y;
         r=new_points[0].r; g=new_points[0].g; b =new_points[0].b;
        
    }
  
    
    glBegin(GL_POINTS);
   
    glColor3d(r, g, b);
    glVertex3f(x1, y1, 0); //point a
    glVertex3f(x2, y2, 0); //point b
    glVertex3f(x3, y3, 0); //point c
    glVertex3f(x4, y4, 0); //point d
//  glVertex3f(33, y4, 0);
//  glVertex3f(81, y4, 0);
//  glVertex3f(129, y4, 0);
//  glVertex3f(369, y4, 0);
//  glVertex3f(417, y4, 0);
//  glVertex3f(465, y4, 0);
    glEnd();
    glPopMatrix();
    glFlush();
    x1_hy=maxheight(x1);
    x2_hy=maxheight(x2);
    x3_hy=maxheight(x3);
    x4_hy=maxheight(x4);
 
    if ((x1_hy == 36 || x2_hy == 36 || x3_hy == 36 || x4_hy == 36)&& begin ) {
            y1-=1 ;
            y2-=1 ;
            y3-=1 ;
            y4-=1 ;
            if ( y1==37 || y2==37  || y3==37  || y4==37 ) {
                begin = false;
            }
            glutPostRedisplay();
      

    }
    else if((y1)>(x1_hy+1) && y2>(x2_hy+1) && y3>(x3_hy+1) && y4>(x4_hy+1)){
        y1-=1 ;
        y2-=1 ;
        y3-=1 ;
        y4-=1 ;
        glutPostRedisplay();
    }
    else {
        square add_p1;
        add_p1.x=x1; add_p1.y=yrange(y1); add_p1.r=r; add_p1.g=g; add_p1.b=b;
        square add_p2;
        add_p2.x=x2; add_p2.y=yrange(y2); add_p2.r=r; add_p2.g=g; add_p2.b=b;
        square add_p3;
        add_p3.x=x3; add_p3.y=yrange(y3); add_p3.r=r; add_p3.g=g; add_p3.b=b;
        square add_p4;
        add_p4.x=x4; add_p4.y=yrange(y4); add_p4.r=r; add_p4.g=g; add_p4.b=b;
       
        points[count]=add_p1;
        count++;
        points[count]=add_p2;
        count++;
        points[count]=add_p3;
        count++;
        points[count]=add_p4;
        count++;
        end = isEnd();
        shoot=true;
        glutPostRedisplay();
    }
  }
  else {
   //   for (int i=0; i<count; i++) { // clearing the array
   //      points[i].x=0;
   //       points[i].y=0;
   //       points[i].r=0;
   //       points[i].g=0;
    //      points[i].b=0;
    //  }
      endgame=true;
     glutPostRedisplay();

  }}
 //   void animate(){
        
   // }
   else {
       glColor3f(01.0,0,0);
       char * stC[100];
       sprintf((char *)stC,"Please press S to start the game");
       print(100,450,(char *)stC);
       sprintf((char *)stC,"Press X to move the shape right");
       print(100,410,(char *)stC);
       sprintf((char *)stC,"Press Z to move the shape left");
       print(100,370,(char *)stC);
       glPopMatrix();
       glFlush();
       glutPostRedisplay();

   }
  }

square * shapes_intialization() {
     shape  = rand() % 7 + 1;

      pshape=cshape;
      cshape=shape;
    if(pshape==cshape){
        shape  = rand() % 7 + 1;
        cshape=shape;

    }
    if(pshape==cshape){
        shape  = rand() % 7 + 1;
        cshape=shape;
        
    }

//    if (begin) {
//    
//        if (cshape==pfshape) {
//            shape  = rand() % 7 + 1;
//            pfshape=fshape;
//            fshape=shape;
//        }
//    }
   
    
    square * r;
    switch (shape) {
        case 1 :
            r = s1_int();
            break;
         case 2:
            r = s2_int();
            break;
        case 3:
            r = s3_int();
            break;
        case 4:
            r = s4_int();
            break;
        case 5:
            r = s5_int();
            break;
       case 6:
            r = s6_int();
            break;
        case 7:
            r = s7_int();
            break;
        default:
            break;
    }
    return r;
}
    square * s1_int(){
    square a;
    square b;
    square c;
    square d;
    a.x=s1_x1; a.y=s1_y; a.r=0.53; a.g=0.94; a.b=0.94;
    b.x=s1_x2; b.y=s1_y; b.r=0.53; b.g=0.94; b.b=0.94;
    c.x=s1_x3; c.y=s1_y; c.r=0.53; c.g=0.94; c.b=0.94;
    d.x=s1_x4; d.y=s1_y; d.r=0.53; d.g=0.94; d.b=0.94;
    square r [4];
    r[0]= a; r[1]= b; r[2]= c; r[3]= d;
    return r;
}
square * s2_int(){
    square a;
    square b;
    square c;
    square d;
    a.x=s2_x1; a.y=s2_y1; a.r=0.0117647; a.g=0.0117647; a.b=0.796;
    b.x=s2_x2; b.y=s2_y2; b.r=0.0117647; b.g=0.0117647; b.b=0.796;
    c.x=s2_x3; c.y=s2_y3; c.r=0.0117647; c.g=0.0117647; c.b=0.796;
    d.x=s2_x4; d.y=s2_y4; d.r=0.0117647; d.g=0.0117647; d.b=0.796;
    square r [4];
    r[0]= a; r[1]= b; r[2]= c; r[3]= d;
    return r;
}
square * s3_int(){
    square a;
    square b;
    square c;
    square d;
    a.x=s3_x1; a.y=s3_y1; a.r=0.74509; a.g=0.541176; a.b=0.13725;
    b.x=s3_x2; b.y=s3_y2; b.r=0.74509; b.g=0.541176; b.b=0.13725;
    c.x=s3_x3; c.y=s3_y3; c.r=0.74509; c.g=0.541176; c.b=0.13725;
    d.x=s3_x4; d.y=s3_y4; d.r=0.74509; d.g=0.541176; d.b=0.13725;
    square r [4];
    r[0]= a; r[1]= b; r[2]= c; r[3]= d;
    return r;
}
square * s4_int(){
    square a;
    square b;
    square c;
    square d;
    a.x=s4_x1; a.y=s4_y1; a.r=0.941176; a.g=0.941176; a.b=0.2196;
    b.x=s4_x2; b.y=s4_y2; b.r=0.941176; b.g=0.941176; b.b=0.2196;
    c.x=s4_x3; c.y=s4_y3; c.r=0.941176; c.g=0.941176; c.b=0.2196;
    d.x=s4_x4; d.y=s4_y4; d.r=0.941176; d.g=0.941176; d.b=0.2196;
    square r [4];
    r[0]= a; r[1]= b; r[2]= c; r[3]= d;
    return r;
}
square * s5_int(){
    square a;
    square b;
    square c;
    square d;
    a.x=s5_x1; a.y=s5_y1; a.r=0.529411; a.g=0.941176; a.b=0.2196;
    b.x=s5_x2; b.y=s5_y2; b.r=0.529411; b.g=0.941176; b.b=0.2196;
    c.x=s5_x3; c.y=s5_y3; c.r=0.529411; c.g=0.941176; c.b=0.2196;
    d.x=s5_x4; d.y=s5_y4; d.r=0.529411; d.g=0.941176; d.b=0.2196;
    square r [4];
    r[0]= a; r[1]= b; r[2]= c; r[3]= d;
    return r;
}
square * s6_int(){
    square a;
    square b;
    square c;
    square d;
    a.x=s6_x1; a.y=s6_y1; a.r=0.5372; a.g=0; a.b=0.92549;
    b.x=s6_x2; b.y=s6_y2; b.r=0.5372; b.g=0; b.b=0.92549;
    c.x=s6_x3; c.y=s6_y3; c.r=0.5372; c.g=0; c.b=0.92549;
    d.x=s6_x4; d.y=s6_y4; d.r=0.5372; d.g=0; d.b=0.92549;
    square r [4];
    r[0]= a; r[1]= b; r[2]= c; r[3]= d;
    return r;
}
square * s7_int(){
    square a;
    square b;
    square c;
    square d;
    a.x=s7_x1; a.y=s7_y1; a.r=0.8078; a.g=0.00392; a.b=0;
    b.x=s7_x2; b.y=s7_y2; b.r=0.8078; b.g=0.00392; b.b=0;
    c.x=s7_x3; c.y=s7_y3; c.r=0.8078; c.g=0.00392; c.b=0;
    d.x=s7_x4; d.y=s7_y4; d.r=0.8078; d.g=0.00392; d.b=0;
    square r [4];
    r[0]= a; r[1]= b; r[2]= c; r[3]= d;
    return r;
}

bool isEnd(){
    for (int j=0; j < count;j++) {
        if(points[j].x == 177 ||points[j].x == 225 ||points[j].x == 273 ||points[j].x == 321 || points[j].x == 202 ||points[j].x ==250||points[j].x == 298){
            if(points[j].y >= 728){
                return true;
            }
        }
    }return false;
}

int maxheight (int x){
    int hyy=36;
    for (int j=0; j < count;j++) {
        if(points[j].x == x){
            if(points[j].y >= hyy){
                hyy=points[j].y;
            }
        }
    }if (hyy==36) {
        return 36;
    }
    return hyy+53;
}

bool leftx (int x,int y){
    int lx=x-48;
    for (int j=0; j < count;j++) {
        if(points[j].y == y){
            if(points[j].x == lx){
                return false;
            }
          }
    }
return true;
}
bool rightx (int x,int y){
    int rx=x+48;
    for (int j=0; j < count;j++) {
        if(points[j].y == y){
            if(points[j].x == rx){
                return false;
            }
        }
    }
    return true;
}


void MyKeyboard (unsigned char key, int x, int y)
{
    bool xl1=leftx(x1, yrange(y1));     bool xr1=rightx(x1, yrange(y1));
    bool xl2=leftx(x2, yrange(y2));     bool xr2=rightx(x2, yrange(y2));
    bool xl3=leftx(x3, yrange(y3));     bool xr3=rightx(x3, yrange(y3));
    bool xl4=leftx(x4, yrange(y4));     bool xr4=rightx(x4, yrange(y4));
    switch (key) {
        case 'z':
            if (x1 != 33 && x2 != 33 && x3 != 33 && x4 != 33 && xl1 && xl2 && xl3 && xl4){
            x1-=48;
            x2-=48;
            x3-=48;
            x4-=48;
            }
            break;
        case 'x':
            if (x1 != 465 && x2 != 465 && x3 != 465 && x4 != 465  && xr1 && xr2 && xr3 && xr4){
            x1+=48;
            x2+=48;
            x3+=48;
            x4+=48;
            }
            break;
        case 's':
            start=1;
            break;
        default:
      break;
    }
    
   }
int yrange(int y){
    (y<91)?y=37:(y<145)?y=91:(y<199)?y=145:(y<253)?y=199:(y<307)?y=253:(y<361)?y=307:(y<415)?y=361:(y<469)?y=415:(y<523)?y=469:(y<577)?y=523:(y<631)?y=577:(y<685)?y=631:(y<739)?y=685:y=739;
    return y;
}
void scoreC(){
    int s=0;
    int ycheck=37;
    int sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
            score+=10;
         removey(ycheck);
    }
    ycheck=91;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }

    ycheck=145;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }

    ycheck=199;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }

    
    ycheck=253;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }

    ycheck=307;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }

    ycheck=361;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }
    ycheck=415;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }


    ycheck=469;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }

    ycheck=523;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }

    ycheck=577;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }

    ycheck=631;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }
    ycheck=685;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }
    ycheck=739;
    sum=0;
    for(int i=0; i<count;i++){
        if(points[i].y== ycheck ){
            sum+=1;
        }
    }
    if (sum==10){
        score+=10;
        removey(ycheck);
    }

   
}
void removey(int y){
    
    
     for(int i=0; i<count;i++){
         if(points[i].y== y ){
             points[i].y = NULL;
              points[i].x = NULL;
         }
          if(points[i].y > y ){
              points[i].y-=54 ;
     }
    yremove=0;
}
}


//void Display()
//{
//glClear(GL_COLOR_BUFFER_BIT);

// glPushMatrix();


/*glColor3f(1.0f,0.0f,0.0f);
 glBegin(GL_POINTS);
 glVertex3f(100.0f, 100.0f, 0.0f);
 glVertex3f(200.0f, 100.0f, 0.0f);
 glEnd( );*/

/*glBegin(GL_LINES);
 glColor3f(1.0f,0.0f,0.0f);
 glVertex3f(10.0f, 10.0f, 0.0f);
 //glVertex3f(20.0f, 20.0f, 0.0f);
 //glVertex3f(30.0f, 30.0f, 0.0f);
 glColor3f(0.0f,0.0f,1.0f);
 glVertex3f(200.0f, 200.0f, 0.0f);
 glEnd( ); */

/*glBegin(GL_LINES);//GL_LINE_STRIP GL_LINE_LOOP
 //glColor3f(1.0f,0.0f,0.0f);
 glVertex3f(10.0f, 10.0f, 0.0f);
 glVertex3f(20.0f, 20.0f, 0.0f);
 glVertex3f(35.0f, 30.0f, 0.0f);
 //glColor3f(0.0f,0.0f,1.0f);
 glVertex3f(200.0f, 255.0f, 0.0f);
 glEnd( );*/

/*glBegin(GL_TRIANGLES);
 glColor3f(1.0f,0.0f,0.0f);
 glVertex3f(100.0f, 100.0f, 0.0f);
 glColor3f(0.0f,1.0f,0.0f);
 glVertex3f(150.0f, 100.0f, 0.0f);
 glColor3f(0.0f,0.0f,1.0f);
 glVertex3f(125.0f, 50.0f, 0.0f);
 glEnd( );*/

/*glBegin(GL_TRIANGLES); //GL_TRIANGLE_STRIP GL_TRIANGLE_FAN
 glVertex3f(100.0f, 100.0f, 0.0f);
 glVertex3f(150.0f, 100.0f, 0.0f);
 glVertex3f(125.0f, 50.0f, 0.0f);
 
 glVertex3f(150.0f, 150.0f, 0.0f);
 glVertex3f(250.0f, 250.0f, 0.0f);
 glVertex3f(350.0f, 150.0f, 0.0f);
 glEnd( );*/

/*glBegin(GL_QUADS); //GL_QUAD_STRIP
 glVertex3f(100.0f, 100.0f, 0.0f);
 glVertex3f(100.0f, 200.0f, 0.0f);
 glVertex3f(200.0f, 200.0f, 0.0f);
 glVertex3f(200.0f, 100.0f, 0.0f);
 
 glVertex3f(300.0f, 300.0f, 0.0f);
 glVertex3f(500.0f, 500.0f, 0.0f);
 glVertex3f(700.0f, 500.0f, 0.0f);
 glVertex3f(500.0f, 300.0f, 0.0f);
 glEnd();*/

/*glBegin(GL_POLYGON);
 glVertex3f(100.0f, 100.0f, 0.0f);
 glVertex3f(100.0f, 200.0f, 0.0f);
 glVertex3f(200.0f, 200.0f, 0.0f);
 glVertex3f(200.0f, 100.0f, 0.0f);
 glVertex3f(300.0f, 300.0f, 0.0f);
 glVertex3f(500.0f, 500.0f, 0.0f);
 glVertex3f(700.0f, 500.0f, 0.0f);
 glVertex3f(500.0f, 300.0f, 0.0f);
 glEnd();*/

//glPopMatrix();
//glFlush();
//}

