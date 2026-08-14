#include <GL/glut.h>
#include "man.h"
#include "gridutils.h"

void drawMan(int row, int col, int cellSize, int windowSize)
{
    int x, y;
    cellOrigin(row, col, cellSize, windowSize, x, y);

    // The figure below was originally designed in its own coordinate
    // space, spanning roughly x:[80,420] (width 340) and y:[70,630]
    // (height 560). We scale it to fit inside one cell, then center
    // it in the cell.
    const float DESIGN_W = 340.0f;
    const float DESIGN_H = 560.0f;
    float scale = (cellSize * 0.85f) / DESIGN_H;

    float scaledW = DESIGN_W * scale;
    float scaledH = DESIGN_H * scale;
    float centerOffsetX = (cellSize - scaledW) / 2.0f;
    float centerOffsetY = (cellSize - scaledH) / 2.0f;

    glPushMatrix();
        glTranslatef((float)x + centerOffsetX, (float)y + centerOffsetY, 0.0f);
        glScalef(scale, scale, 1.0f);
        glTranslatef(-80.0f, -70.0f, 0.0f);

        // ---------------- man figure, unchanged ----------------
   glColor3f( 0.87 ,0.357, 0.239);

   glBegin(GL_POLYGON);
   glVertex2i(150,550);
   glVertex2i(350,550);
   glVertex2i(350,580);
   glVertex2i(150,580);

   glVertex2i(160,580);
   glVertex2i(340,550);
   glVertex2i(340,590);
   glVertex2i(160,590);

   glVertex2i(180,590);
   glVertex2i(320,590);
   glVertex2i(320,610);
   glVertex2i(180,610);

   glVertex2i(210,610);
   glVertex2i(290,610);
   glVertex2i(290,620);
   glVertex2i(270,620);
   glVertex2i(270,630);
   glVertex2i(230,630);
   glVertex2i(230,620);
   glVertex2i(210,620);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(150,550);
   glVertex2i(150,580);
   glVertex2i(150,580);
   glVertex2i(160,580);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(5);
   glBegin(GL_LINES);
   glVertex2i(150,550);
   glVertex2i(350,550);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(160,580);
   glVertex2i(160,590);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(160,590);
   glVertex2i(180,590);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(180,590);
   glVertex2i(180,610);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(180,610);
   glVertex2i(210,610);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(210,610);
   glVertex2i(210,620);
   glEnd();

      glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(210,620);
   glVertex2i(230,620);
   glEnd();

      glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(230,620);
   glVertex2i(230,630);
   glEnd();

      glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(230,630);
   glVertex2i(270,630);
   glEnd();

      glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(270,630);
   glVertex2i(270,620);
   glEnd();

      glColor3f( 0.3,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(270,620);
   glVertex2i(290,620);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(290,620);
   glVertex2i(290,610);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(290,610);
   glVertex2i(320,610);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(320,610);
   glVertex2i(320,590);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(320,590);
   glVertex2i(340,590);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(340,590);
   glVertex2i(340,580);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(340,580);
   glVertex2i(350,580);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(350,580);
   glVertex2i(350,550);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(4);
   glBegin(GL_LINES);
   glVertex2i(140,510);
   glVertex2i(160,510);

   glVertex2i(340,510);
   glVertex2i(360,510);

   glVertex2i(140,470);
   glVertex2i(160,470);

   glVertex2i(340,470);
   glVertex2i(360,470);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(140,540);
   glVertex2i(140,550);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(140,550);
   glVertex2i(360,550);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(360,550);
   glVertex2i(360,540);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(360,540);
   glVertex2i(370,540);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(370,540);
   glVertex2i(370,530);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(140,540);
   glVertex2i(130,540);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(130,540);
   glVertex2i(130,530);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(130,530);
   glVertex2i(370,530);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glBegin(GL_POLYGON);
   glVertex2i(130,530);
   glVertex2i(370,530);
   glVertex2i(370,540);
   glVertex2i(130,540);
   glEnd();

   glColor3f( 1 ,0.5, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(140,540);
   glVertex2i(360,540);
   glVertex2i(360,550);
   glVertex2i(140,550);
   glEnd();

   glColor3f( 0.98 ,0.87, 0.80);
   glBegin(GL_POLYGON);
   glVertex2i(140,470);
   glVertex2i(140,460);
   glVertex2i(160,460);
   glVertex2i(160,510);
   glVertex2i(140,510);
   glVertex2i(140,500);
   glVertex2i(130,500);
   glVertex2i(130,470);
   glEnd();

   glColor3f( 0.98 ,0.87, 0.80);
    glBegin(GL_POLYGON);
   glVertex2i(360,470);
   glVertex2i(360,460);
   glVertex2i(340,460);
   glVertex2i(340,510);
   glVertex2i(360,510);
   glVertex2i(360,500);
   glVertex2i(370,500);
   glVertex2i(370,470);
   glEnd();

   glColor3f( 1 ,0.5, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(140,480);
   glVertex2i(160,480);
   glVertex2i(160,490);
   glVertex2i(140,490);
   glEnd();

glColor3f( 1 ,0.5, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(340,480);
   glVertex2i(360,480);
   glVertex2i(360,490);
   glVertex2i(340,490);
   glEnd();

   glColor3f( 0.98 ,0.87, 0.80);
    glBegin(GL_POLYGON);
   glVertex2i(230,410);
   glVertex2i(230,400);
   glVertex2i(270,400);
   glVertex2i(270,410);
   glVertex2i(290,410);
   glVertex2i(290,420);
   glVertex2i(210,420);
   glVertex2i(210,410);
   glVertex2i(230,410);

   glVertex2i(270,420);
   glVertex2i(310,420);
   glVertex2i(310,440);
   glVertex2i(320,440);
   glVertex2i(320,450);
   glVertex2i(180,450);
   glVertex2i(180,440);
   glVertex2i(190,440);
   glVertex2i(190,420);
   glVertex2i(210,420);
   glEnd();

    glColor3f( 0.98 ,0.87, 0.80);
    glBegin(GL_POLYGON);
   glVertex2i(160,450);
   glVertex2i(340,450);
   glVertex2i(340,530);
   glVertex2i(160,530);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(160,450);
   glVertex2i(160,530);

   glVertex2i(340,450);
   glVertex2i(340,530);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(150,530);
   glVertex2i(150,510);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(150,510);
   glVertex2i(140,510);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(140,500);
   glVertex2i(140,510);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(140,500);
   glVertex2i(130,500);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(350,530);
   glVertex2i(350,510);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(350,510);
   glVertex2i(360,510);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(360,500);
   glVertex2i(360,510);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(360,500);
   glVertex2i(370,500);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(370,500);
   glVertex2i(370,470);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(130,500);
   glVertex2i(130,470);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(130,470);
   glVertex2i(140,470);

   glVertex2i(360,470);
   glVertex2i(370,470);

   glVertex2i(140,460);
   glVertex2i(140,470);

   glVertex2i(360,470);
   glVertex2i(360,460);

   glVertex2i(160,460);
   glVertex2i(140,460);

   glVertex2i(360,460);
   glVertex2i(340,460);

   glVertex2i(160,460);
   glVertex2i(160,450);

   glVertex2i(340,460);
   glVertex2i(340,450);

   glVertex2i(160,450);
   glVertex2i(180,450);

   glVertex2i(340,450);
   glVertex2i(320,450);

   glVertex2i(180,450);
   glVertex2i(180,440);

   glVertex2i(320,450);
   glVertex2i(320,440);

   glVertex2i(180,440);
   glVertex2i(190,440);

   glVertex2i(190,440);
   glVertex2i(190,420);

   glVertex2i(190,420);
   glVertex2i(210,420);

   glVertex2i(210,420);
   glVertex2i(210,410);

   glVertex2i(210,410);
   glVertex2i(230,410);

   glVertex2i(230,400);
   glVertex2i(230,410);

   glVertex2i(230,400);
   glVertex2i(270,400);

   glVertex2i(270,410);
   glVertex2i(270,400);

   glVertex2i(270,410);
   glVertex2i(290,410);

   glVertex2i(290,420);
   glVertex2i(290,410);

   glVertex2i(310,420);
   glVertex2i(290,420);

   glVertex2i(310,420);
   glVertex2i(310,440);

   glVertex2i(320,440);
   glVertex2i(310,440);
   glEnd();

glColor3f( 0.0 ,0.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(180,520);
   glVertex2i(230,520);
   glVertex2i(230,530);
   glVertex2i(180,530);
   glEnd();

   glColor3f( 0.0 ,0.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(270,520);
   glVertex2i(320,520);
   glVertex2i(320,530);
   glVertex2i(270,530);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glBegin(GL_POLYGON);
   glVertex2i(190,470);
   glVertex2i(210,470);
   glVertex2i(210,500);
   glVertex2i(190,500);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glBegin(GL_POLYGON);
   glVertex2i(290,470);
   glVertex2i(310,470);
   glVertex2i(310,500);
   glVertex2i(290,500);
   glEnd();

   glColor3f( 0.6 ,0.3, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(230,460);
   glVertex2i(260,460);
   glVertex2i(260,450);
   glVertex2i(230,450);
   glEnd();
   glColor3f( 0.6 ,0.3, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(250,500);
   glVertex2i(260,500);
   glVertex2i(260,460);
   glVertex2i(250,460);
   glEnd();
   glColor3f( 0.5 ,0.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(230,420);
   glVertex2i(270,420);
   glVertex2i(270,430);
   glVertex2i(230,430);
   glEnd();

   glColor3f(0.5, 0.0, 0.0);
   glBegin(GL_LINES);
   glVertex2i(190,420);
   glVertex2i(190,400);
   glVertex2i(190,400);
   glVertex2i(170,400);
   glVertex2i(180,400);
   glVertex2i(180,390);
   glVertex2i(190,390);
   glVertex2i(190,390);
   glVertex2i(190,380);
   glVertex2i(210,380);
   glVertex2i(190,390);
   glVertex2i(190,380);
   glVertex2i(180,390);
   glVertex2i(190,390);
   glVertex2i(210,380);
   glVertex2i(210,370);
   glVertex2i(220,370);
   glVertex2i(210,370);
   glVertex2i(220,370);
   glVertex2i(220,360);
   glVertex2i(280,360);
   glVertex2i(220,360);
   glVertex2i(280,360);
   glVertex2i(280,370);
   glVertex2i(290,370);
   glVertex2i(280,370);
   glVertex2i(290,370);
   glVertex2i(290,380);
   glVertex2i(290,380);
   glVertex2i(310,380);
   glVertex2i(310,380);
   glVertex2i(310,390);
   glVertex2i(320,390);
   glVertex2i(310,390);
   glVertex2i(320,390);
   glVertex2i(320,400);
   glVertex2i(330,400);
   glVertex2i(310,400);
   glVertex2i(310,420);
   glVertex2i(310,400);

   glVertex2i(170,400);
   glVertex2i(170,390);
   glVertex2i(150,390);
   glVertex2i(170,390);
   glVertex2i(150,390);
   glVertex2i(150,380);
   glVertex2i(130,380);
   glVertex2i(150,380);
   glVertex2i(130,380);
   glVertex2i(130,360);
   glVertex2i(130,360);
   glVertex2i(110,360);
   glVertex2i(110,360);
   glVertex2i(110,350);
   glVertex2i(100,350);
   glVertex2i(110,350);

   glVertex2i(330,400);
   glVertex2i(330,390);
   glVertex2i(350,390);
   glVertex2i(330,390);
   glVertex2i(350,390);
   glVertex2i(350,380);
   glVertex2i(370,380);
   glVertex2i(350,380);
   glVertex2i(370,380);
   glVertex2i(370,360);
    glVertex2i(390,360);
   glVertex2i(370,360);
   glVertex2i(390,360);
   glVertex2i(390,350);
   glVertex2i(390,350);
   glVertex2i(400,350);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glBegin(GL_POLYGON);
   glVertex2i(150,390);
   glVertex2i(150,120);
   glVertex2i(160,120);
   glVertex2i(160,390);
   glEnd();
   glColor3f( 0.3 ,0.3, 0.3);
   glBegin(GL_POLYGON);
   glVertex2i(340,390);
   glVertex2i(340,120);
   glVertex2i(350,120);
   glVertex2i(350,390);
   glEnd();

glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(100,350);
   glVertex2i(100,280);
   glVertex2i(400,350);
   glVertex2i(400,280);
   glEnd();
   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(4);
   glBegin(GL_LINES);
   glVertex2i(80,280);
   glVertex2i(150,280);
   glVertex2i(80,250);
   glVertex2i(80,280);
   glVertex2i(80,250);
   glVertex2i(150,250);
   glVertex2i(100,250);
   glVertex2i(100,220);
   glVertex2i(140,220);
   glVertex2i(100,220);
   glVertex2i(140,220);
   glVertex2i(140,250);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(4);
   glBegin(GL_LINES);
   glVertex2i(350,280);
   glVertex2i(420,280);
   glVertex2i(420,280);
   glVertex2i(420,250);
   glVertex2i(420,250);
   glVertex2i(350,250);
   glVertex2i(400,250);
   glVertex2i(400,220);
   glVertex2i(400,220);
   glVertex2i(360,220);
   glVertex2i(360,250);
   glVertex2i(360,220);
   glEnd();
   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(230,200);
   glVertex2i(270,200);
   glVertex2i(270,200);
   glVertex2i(270,70);
   glVertex2i(230,200);
   glVertex2i(230,70);
   glVertex2i(230,70);
   glVertex2i(120,70);
   glVertex2i(270,70);
   glVertex2i(380,70);

   glVertex2i(120,70);
   glVertex2i(120,100);
   glVertex2i(120,100);
   glVertex2i(140,100);
   glVertex2i(140,100);
   glVertex2i(140,110);
   glVertex2i(140,110);
   glVertex2i(150,110);
   glVertex2i(150,120);
   glVertex2i(150,120);
   glVertex2i(160,120);
   glVertex2i(160,120);
   glVertex2i(160,130);


   glVertex2i(230,130);
   glVertex2i(160,130);

   glVertex2i(160,120);
   glVertex2i(160,130);

   glVertex2i(160,120);
   glVertex2i(150,120);

   glVertex2i(150,110);
   glVertex2i(150,120);
   glEnd();

   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(270,130);
   glVertex2i(340,130);

   glVertex2i(340,120);
   glVertex2i(340,130);

   glVertex2i(340,120);
   glVertex2i(350,120);

   glVertex2i(350,110);
   glVertex2i(350,120);

   glVertex2i(350,110);
   glVertex2i(360,110);

   glVertex2i(360,100);
   glVertex2i(360,110);

   glVertex2i(360,100);
   glVertex2i(380,100);

   glVertex2i(380,70);
   glVertex2i(380,100);
   glEnd();

   glColor3f(0.161, 0.349, 0.380);
   glBegin(GL_POLYGON);
   glVertex2i(220,360);
   glVertex2i(280,360);
   glVertex2i(280,280);
   glVertex2i(220,280);
   glEnd();
   glColor3f( 0.0 ,0.0, 0.0);
   glLineWidth(5);
   glBegin(GL_LINES);
   glVertex2i(230,350);
   glVertex2i(270,350);
   glVertex2i(230,330);
   glVertex2i(270,330);
   glVertex2i(230,310);
   glVertex2i(270,310);
   glVertex2i(230,290);
   glVertex2i(270,290);
glEnd();
   glColor3f( 0.5 ,0.0, 0.0);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(160,280);
   glVertex2i(340,280);
   glVertex2i(160,250);
   glVertex2i(340,250);
   glEnd();
   glColor3f( 0.5 ,0.5, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(220,280);
   glVertex2i(280,280);
   glVertex2i(280,250);
   glVertex2i(220,250);
   glEnd();
    glColor3f( 0.984, 0.788, 0.353);
   glBegin(GL_POLYGON);
   glVertex2i(230,270);
   glVertex2i(270,270);
   glVertex2i(270,260);
   glVertex2i(230,260);
   glEnd();
   glColor3f( 0.984, 0.788, 0.353);
   glBegin(GL_POLYGON);
   glVertex2i(160,280);
   glVertex2i(220,280);
   glVertex2i(220,250);
   glVertex2i(160,250);
   glEnd();
   glColor3f( 0.984, 0.788, 0.353);
   glBegin(GL_POLYGON);
   glVertex2i(280,280);
   glVertex2i(340,280);
   glVertex2i(340,250);
   glVertex2i(280,250);
   glEnd();

glColor3f( 0.871, 0.357, 0.239);
   glBegin(GL_POLYGON);
   glVertex2i(190,390);
   glVertex2i(190,380);
   glVertex2i(210,380);
   glVertex2i(210,370);
   glVertex2i(220,370);
   glVertex2i(220,280);
   glVertex2i(160,280);
   glVertex2i(160,390);
   glVertex2i(170,390);
   glVertex2i(170,400);
   glVertex2i(180,400);
   glVertex2i(180,390);
   glVertex2i(190,390);
   glEnd();

   glColor3f( 0.871, 0.357, 0.239);
   glBegin(GL_POLYGON);
   glVertex2i(310,390);
   glVertex2i(310,380);
   glVertex2i(290,380);
   glVertex2i(290,370);
   glVertex2i(280,370);
   glVertex2i(280,280);
   glVertex2i(340,280);
   glVertex2i(340,390);
   glVertex2i(330,390);
   glVertex2i(330,400);
   glVertex2i(320,400);
   glVertex2i(320,390);
   glVertex2i(310,390);
   glEnd();


   glColor3f( 1.0, 0.85, 0.43);
   glBegin(GL_POLYGON);
   glVertex2i(170,330);
   glVertex2i(170,300);
   glVertex2i(190,300);
   glVertex2i(190,330);
   glEnd();
   glColor3f( 1.0, 0.85, 0.43);
   glBegin(GL_POLYGON);
   glVertex2i(160,330);
   glVertex2i(200,330);
   glVertex2i(200,345);
   glVertex2i(160,345);
   glEnd();

   glColor3f( 1.0, 0.85, 0.43);
   glBegin(GL_POLYGON);
   glVertex2i(310,330);
   glVertex2i(310,300);
   glVertex2i(330,300);
   glVertex2i(330,330);
   glEnd();
   glColor3f( 1.0, 0.85, 0.43);
   glBegin(GL_POLYGON);
   glVertex2i(300,330);
   glVertex2i(340,330);
   glVertex2i(340,345);
   glVertex2i(300,345);
   glEnd();
   glColor3f( 0.16, 0.35, 0.38);
   glBegin(GL_POLYGON);
   glVertex2i(160,200);
   glVertex2i(340,200);
   glVertex2i(340,250);
   glVertex2i(160,250);

   glVertex2i(160,200);
   glVertex2i(230,200);
   glVertex2i(230,130);
   glVertex2i(160,130);
   glEnd();

   glColor3f( 0.16, 0.35, 0.38);
   glBegin(GL_POLYGON);
   glVertex2i(270,200);
   glVertex2i(270,130);
   glVertex2i(340,130);
   glVertex2i(340,200);
   glEnd();


   glColor3f( 0.0, 0.75, 1.0);
   glBegin(GL_POLYGON);
   glVertex2i(190,390);
   glVertex2i(190,380);
   glVertex2i(310,380);
   glVertex2i(310,390);
   glVertex2i(320,390);
   glVertex2i(320,400);
   glVertex2i(180,400);
   glVertex2i(180,390);
   glEnd();

    glColor3f( 0.0, 0.75, 1.0);
   glBegin(GL_POLYGON);
   glVertex2i(290,410);
   glVertex2i(270,410);
   glVertex2i(270,400);
   glVertex2i(310,400);
   glVertex2i(310,420);
   glVertex2i(290,420);
   glEnd();

   glColor3f( 0.0, 0.75, 1.0);
   glBegin(GL_POLYGON);
   glVertex2i(210,410);
   glVertex2i(230,410);
   glVertex2i(230,400);
   glVertex2i(190,400);
   glVertex2i(190,420);
   glVertex2i(210,420);
   glEnd();

   glColor3f( 0.0, 0.75, 1.0);
   glBegin(GL_POLYGON);
   glVertex2i(220,370);
   glVertex2i(220,360);
   glVertex2i(280,360);
   glVertex2i(280,370);
   glVertex2i(290,370);
   glVertex2i(290,380);
   glVertex2i(210,380);
   glVertex2i(210,370);
   glVertex2i(220,370);
   glEnd();

   glColor3f( 0.0, 0.75, 1.0);
   glBegin(GL_POLYGON);
   glVertex2i(130,360);
   glVertex2i(110,360);
   glVertex2i(110,350);
   glVertex2i(100,350);
   glVertex2i(100,280);
   glVertex2i(150,280);
   glVertex2i(150,380);
   glVertex2i(130,380);
   glVertex2i(130,360);
   glEnd();

   glColor3f( 0.0, 0.75, 1.0);
   glBegin(GL_POLYGON);
   glVertex2i(370,360);
   glVertex2i(390,360);
   glVertex2i(390,350);
   glVertex2i(400,350);
   glVertex2i(400,280);
   glVertex2i(350,280);
   glVertex2i(350,380);
   glVertex2i(370,380);
   glVertex2i(370,360);
   glEnd();
   glColor3f( 0.98, 0.87, 0.80);
   glBegin(GL_POLYGON);
   glVertex2i(100,250);
   glVertex2i(100,220);
   glVertex2i(140,220);
   glVertex2i(140,250);
   glVertex2i(100,250);
   glEnd();

   glColor3f( 0.98, 0.87, 0.80);
   glBegin(GL_POLYGON);
   glVertex2i(400,250);
   glVertex2i(400,220);
   glVertex2i(360,220);
   glVertex2i(360,250);
   glVertex2i(400,250);
   glEnd();

   glColor3f( 1, 0.5, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(80,279);
   glVertex2i(80,252);
   glVertex2i(150,252);
   glVertex2i(150,279);
   glVertex2i(80,279);
   glEnd();

   glColor3f( 1, 0.5, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(420,279);
   glVertex2i(420,252);
   glVertex2i(350,252);
   glVertex2i(350,279);
   glVertex2i(420,279);
   glEnd();

   glColor3f( 0.3 ,0.3, 0.3);
   glLineWidth(3);
   glBegin(GL_LINES);
   glVertex2i(160,280);
   glVertex2i(340,280);
   glVertex2i(160,250);
   glVertex2i(340,250);
   glEnd();

   glColor3f( 0.0, 0.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(120,70);
   glVertex2i(230,70);
   glVertex2i(230,80);
   glVertex2i(120,80);
   glEnd();
   glColor3f( 0.0, 0.0, 0.0);
   glBegin(GL_POLYGON);
   glVertex2i(270,70);
   glVertex2i(380,70);
   glVertex2i(380,80);
   glVertex2i(270,80);
   glEnd();

   glColor3f(0.396, 0.208, 0.122);
   glBegin(GL_POLYGON);
   glVertex2i(150,110);
   glVertex2i(140,110);
   glVertex2i(140,100);
   glVertex2i(120,100);
   glVertex2i(120,80);
   glVertex2i(230,80);
   glVertex2i(230,130);
   glVertex2i(160,130);
   glVertex2i(160,120);
   glVertex2i(150,120);
   glVertex2i(150,110);
   glEnd();

   glColor3f(0.396, 0.208, 0.122);
   glBegin(GL_POLYGON);
   glVertex2i(350,110);
   glVertex2i(360,110);
   glVertex2i(360,100);
   glVertex2i(380,100);

   glVertex2i(380,80);
   glVertex2i(270,80);
   glVertex2i(270,130);
   glVertex2i(340,130);
   glVertex2i(340,120);
   glVertex2i(350,120);
   glVertex2i(350,110);
   glEnd();

   glColor3f(0.396, 0.208, 0.122);
   glBegin(GL_POLYGON);
   glVertex2i(120,80);
   glVertex2i(230,80);
   glVertex2i(230,90);
   glVertex2i(130,90);
   glEnd();
        // -------------- end man figure --------------

    glPopMatrix();
}
