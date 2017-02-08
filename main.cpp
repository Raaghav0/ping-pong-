#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <thread>
#include <iostream>
#include <math.h>
#include <windows.h>

using namespace std;

void setup() {   glClearColor(1.0f, 1.0f, 1.0f, 1.0f); }
void rect1();
void rect2();
void circle();
float getYmax(int);
float getYmin(int);
float getBallXmax();
float getBallYmax();
float getBallXmin();
float getBallYmin();
bool hitposx();
bool hitnegx();
bool hitposy();
bool hitnegy();
void moveplayer1();
void moveplayer2();
void moveball();
void specialKey(int,int,int);
void mouse_action(int,int,int,int);

float rect1_X = -0.8 , rect1_Y = 0 , rect2_X = 0.8 , rect2_Y = 0 ;
float xwidth_1 = 0.06 , ywidth_1 = 0.3 , xwidth_2 = 0.06 , ywidth_2 = 0.3;
float moveunit = 0.1f;
int player1_up = 0 , player1_down = 0;
int player2_up = 0 , player2_down = 0;
float centerx = 0 ,centery = 0;
int direction = 45 ;

float radius = 0.07 ;
float pi = 3.1416;

void display()
{
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glColor3f(0.0f, 0.0f, 0.0f);
      rect1();
      rect2();
      circle();
      glutSwapBuffers();
}

void rect1()
{
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(-xwidth_1 + rect1_X, -ywidth_1 + rect1_Y);
    glVertex2f(-xwidth_1 + rect1_X, ywidth_1 + rect1_Y);
    glVertex2f(xwidth_1 + rect1_X, ywidth_1 + rect1_Y);
    glVertex2f(xwidth_1 + rect1_X, -ywidth_1 + rect1_Y);
    glEnd();
}

void rect2()
{
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(-xwidth_2 + rect2_X, -ywidth_2 + rect2_Y);
    glVertex2f(-xwidth_2 + rect2_X, ywidth_2 + rect2_Y);
    glVertex2f(xwidth_2 + rect2_X, ywidth_2 + rect2_Y);
    glVertex2f(xwidth_2 + rect2_X, -ywidth_2 + rect2_Y);
    glEnd();
}

int main(int argc, char *argv[])
  {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
     glutInitWindowPosition(100,100);
     glutInitWindowSize(1200,1000);
     glutCreateWindow("Hello World");
     setup();
     glutDisplayFunc(display);
     glutSpecialFunc(specialKey);
     glutMouseFunc(mouse_action);

     thread player1(moveplayer1);
     thread player2(moveplayer2);
     thread ball(moveball);

     glutMainLoop();
     player1.join();
     player2.join();
     ball.join();
     return 0;
  }

  void specialKey(int key , int x ,int y)
  {

      switch (key){
        case GLUT_KEY_RIGHT:
            //posX+=move_unit;;
            break;

        case GLUT_KEY_LEFT:
            //posX-=move_unit;;
        break;

        case GLUT_KEY_UP:
            player1_up = 1;
            break;

        case GLUT_KEY_DOWN:
            player1_down = 1;
        break;

        default:
         break;
    }
  }


  void mouse_action(int button , int state ,int x , int y)
  {

      if (button == GLUT_LEFT_BUTTON)
      {
          player2_down = 1;
      }else if (button == GLUT_RIGHT_BUTTON)
      {
          player2_up = 1;
      }else{

      }
  }

  void moveplayer1()
  {

      while(1)
      {

          if (player1_up == 1 && getYmax(1) < 0.95)
          {
              rect1_Y += moveunit;
              player1_up = 0;
              glutPostRedisplay();
          }
          else if (player1_down == 1 && getYmin(1) > -0.95)
          {
              rect1_Y -= moveunit;
              player1_down = 0;
              glutPostRedisplay();
          }
          else{}
      }
  }

  void moveplayer2()
  {

      while(1)
      {

          if (player2_up == 1 && getYmax(2) < 0.95)
          {
              rect2_Y += moveunit;
              player2_up = 0;
              glutPostRedisplay();
          }
          else if (player2_down == 1 && getYmin(2) > -0.95 )
          {
              rect2_Y -= moveunit;
              player2_down = 0;
              glutPostRedisplay();
          }
          else{}
      }
  }

  float getYmax(int number)
  {

      if(number == 1)
      {
          return rect1_Y + ywidth_1;
      }
      return rect2_Y + ywidth_2;
  }

  float getYmin(int number)
  {

      if(number == 1)
      {
          return rect1_Y - ywidth_1;
      }
      return rect2_Y - ywidth_2;
  }

  void circle()
  {
      glBegin(GL_POLYGON);
      glColor3f(1.0,0,0);
      for(float i = 0;i< 2*pi ;i+=(pi/30))
      {
        i = double(i);
        glVertex2f((float)(cos(i))*radius + centerx ,  radius* (float)(sin(i)) + centery);
        i = float(i);
      }
      glEnd();
  }

  void moveball()
  {

    while(1)
    {
      //implement moveball() function here
      if (hitposx())
      {
          if(direction == 135)direction =45;
          else direction = -45;
      }
      else if(hitposy())
      {
          if(direction == -45)direction = 45 ;
          else direction = 135;
      }
      else if(hitnegy())
      {
          if(direction == 45)direction = -45 ;
          else direction = -135;
      }
      else if(hitnegx())
      {
          if(direction == -45)direction = -135 ;
          else direction = 135;
      }
      else{}

      centerx += radius * cos(direction/180 * pi);
      centery += radius * sin(direction/180 * pi);
      Sleep(150);
      glutPostRedisplay();
    }
  }

  float getBallXmax()
  {
      return centerx + radius;
  }

  float getBallXmin()
  {
      return centerx - radius;
  }

  float getBallYmax()
  {
      return centery + radius;
  }

  float getBallYmin()
  {
      return centery - radius;
  }

  bool hitposx()
  {
      if (getBallXmin() <= -0.75)return true;
      return false;
  }

  bool hitnegx()
  {
      if (getBallXmax() >= 0.75)return true;
      return false;
  }

  bool hitposy()
  {
      if (getBallYmin() <= -0.95)return true;
      return false;
  }

  bool hitnegy()
  {
      if (getBallYmax() >= 0.95)return true;
      return false;
  }

