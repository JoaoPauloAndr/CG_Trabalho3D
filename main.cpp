#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "includes/xml_parsing.h"
#include "includes/info.h"
#include "includes/game_platforms.h"
#include "includes/character.h"
#include "includes/player.h"

/*
*
*
TODO:
  - Win (end of arena)
  - Display message and freeze the game
  - Shoot
  - Illumination
  - Lights out mode
*/

Arena arena_info;
Platforms platforms;
Enemies_info enemies_info;
Character_info player_info;
Player player;
Player *pPlayer = &player; 

//Key status
int keyStatus[256];

//Mouse aim
int mouseAim;

//Controls animation
int animate = 0;

//Camera mode
int camera_mode = 3;

//Camera rotation
bool camera_rotation = false;
double camXYAngle= 30;
double camXZAngle= -90;
int lastCamX = 0;
int lastCamY = 0;
int zoom = (SCALE - 0.3) * 40;

void keyPress(unsigned char key, int x, int y)
{
  switch (key)
  {
      case '9':
            animate = !animate;
            break;
      case '1':
            camera_mode = 1;
            break;
      case '2':
            camera_mode = 2;
            break;      
      case '3':
            camera_mode = 3;
            break;            
      case 'w':
      case 'W':
            keyStatus[(int)('w')] = 1;
            break;
      case 's':
      case 'S':
            keyStatus[(int)('s')] = 1;
            break;
      case 'a':
      case 'A':
            keyStatus[(int)('a')] = 1;
            break;
      case 'd':
      case 'D':
            keyStatus[(int)('d')] = 1;
            break;             
      case ' ':
            keyStatus[(int)(' ')] = 1;
            break;
      case 'v':
      case 'V':
            keyStatus[(int)('v')] = 1;
            break;
      case 'r':
      case 'R':
            keyStatus[(int)('r')] = 1;
            break;
      case 'x':
      case 'X':
            keyStatus[(int)('x')] = 1;
            break;
      case '+':
        zoom++;
        break;
    case '-':
        zoom--;
         break;                  
      case 27 :
            exit(0);
  }
  glutPostRedisplay();
}

void ResetKeyStatus()
{
  int i;
  //Initialize keyStatus
  for(i = 0; i < 256; i++)
    keyStatus[i] = 0; 
}

void keyup(unsigned char key, int x, int y)
{
  keyStatus[(int)(key)] = 0;
  glutPostRedisplay();
}

void idle(void)
{
  camera_rotation = false;
  
  //MoveX
  bool isRunning = false;
  GLfloat vel = 0;
  if(keyStatus[(int)('w')])
  {
    isRunning = true;
    vel = VEL;
  }

  if(keyStatus[(int)('s')])
  {
    isRunning = true;
    vel = -VEL;
  }

  //Rotation
  if(keyStatus[(int)('a')])
  {
    player.RotateZ(INC_DIRECTION);
  }

  if(keyStatus[(int)('d')])
  {
    player.RotateZ(-INC_DIRECTION);
  }

  //MoveY
  if(keyStatus[(int)(' ')])
  {

    if(player.getIsGrounded())
    {
      player.Jump();
    }

    if(player.getIsJumping() && player.getJumCounter() > 0)
    {
      player.Jump();
    }
  }

  if(keyStatus[(int)(' ')] == 0)
  {
    player.resetJump();
  }

  if(keyStatus[(int)('v')])
  {
    player.MoveY(-INC_DY);
  }

  //Control camera rotation
  if(keyStatus[(int)('x')] && camera_mode == 3)
  {
    camera_rotation = true;
  }

  player.HandleInput(isRunning, vel);
  //player.Shoot();
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  switch (camera_mode)
  {
  case 1:
    gluLookAt(
      player.getEyesX(), player.getEyesY(), player.getEyesZ(),
      player.getEyesX() + 1 * cos(player.getDiretion() * M_PI/180), 
      player.getEyesY(), 
      player.getEyesZ() - 1 * sin(player.getDiretion() * M_PI/180), 
      0,1,0
    );
    break;
  case 2:
    gluLookAt(
      player.getRightArmX(), player.getRightArmY(), player.getRightArmZ(),
      player.getRightArmX() + 1 * cos(player.getDiretion() * M_PI/180),
      player.getRightArmY() + 1 * sin(player.getArmTheta() * M_PI/180),
      player.getRightArmZ() - 1 * sin(player.getDiretion() * M_PI/180),
      0,1,0
    );
    break;  
  default:  //camera_mode == 3
    gluLookAt(
      player.getX() + zoom*sin(camXZAngle*M_PI/180)*cos((camXYAngle*M_PI/180)), 
      player.getCenterY() + zoom*sin((camXYAngle*M_PI/180)), 
      player.getZ() + zoom*cos(camXZAngle*M_PI/180)*cos((camXYAngle*M_PI/180)),
      player.getX(), player.getCenterY(), player.getZ(), 
      0,1,0
    );
    break;
  }

  /*GLfloat light_position[] = { 1.0, 5.0, 2.0, 1.0 };
  glLightfv(  GL_LIGHT0, GL_POSITION, light_position);*/

  //Lightning
  GLfloat light_position[] = {arena_info.length/2, arena_info.height, arena_info.width/2, 1};
  glLightfv(GL_LIGHT0,GL_POSITION,light_position);
  /*glDisable(GL_LIGHTING);
      glPointSize(15);
      glColor3f(1.0,1.0,0.0);
      glBegin(GL_POINTS);
          glVertex3f(light_position[0],light_position[1],light_position[2]);
      glEnd();    
  glEnable(GL_LIGHTING);*/

  //Platforms
  glPushMatrix();
    drawPlatforms(platforms, arena_info.width, pPlayer);
  glPopMatrix();

  //Characters
  glPushMatrix();
    player.Draw();
  glPopMatrix();

  // glPushMatrix();
  //   glTranslatef(1,1,10);
  //   glShadeModel(GL_SMOOTH);

  //   GLfloat materialEmission[] = { 0.00, 0.25, 0.00, 1};
  //   GLfloat materialColor[] = { 0.0, 1.0, 0.0, 1};
  //   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
  //   GLfloat mat_shininess[] = { 50.0 };
  //   glColor3f(0,1,0);

  //   glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
  //   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
  //   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  //   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  //   glutSolidSphere(10, 20, 10);

  //   glShadeModel(GL_FLAT);
  // glPopMatrix();
  player.Shoot();  
  
  glutPostRedisplay();

  glutSwapBuffers();
}


void init() 
{
  ResetKeyStatus();
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glShadeModel (GL_FLAT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glViewport (0, 0, (GLsizei) WINDOW_SIZE, 
          (GLsizei) WINDOW_SIZE);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (60, 
                  (GLfloat)WINDOW_SIZE/(GLfloat)WINDOW_SIZE, 
                  1, 1000);  
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //if(!shot) shot = player.Shoot();
        player.Shoot();
        //printf("Pew\n");
    }else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
      //player.Jump();
    }
    if(camera_rotation)
    {
      lastCamX = x;
      lastCamY = y;
      glutPostRedisplay();
    }
}

void motion(int x, int y)
{
  if(camera_rotation)
  {
    camXZAngle -= x - lastCamX;
    camXYAngle += y - lastCamY;

    if(camXYAngle > 60)
    {
      camXYAngle = 60;
    }

    if(camXYAngle < -60)
    {
      camXYAngle = -60;
    }

    lastCamX = x;
    lastCamY = y;
    glutPostRedisplay();
  }
  else
  {
    int delta = y - mouseAim;
    mouseAim = y;
    if(delta < 0){
      player.moveArm(INC_ANGLE);
    }else if(delta > 0){
      player.moveArm(-INC_ANGLE);
    }
  }
}


int main(int argc, char *argv[])
{
  if(argc > 1)
  {
    const char * filename = argv[1];    
    readXml(filename, &arena_info, platforms, enemies_info, &player_info);
    player.Init(player_info.starting_point.x, 
                arena_info.length,
                arena_info.width,
                player_info.head_radius);

    //Initialize openGL
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Create the window
    glutInitWindowSize (WINDOW_SIZE, WINDOW_SIZE);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Trabalho 3D");

    //Callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup);

    init();

    //Mouse
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion); 

    glutMainLoop();
    return 0; 
  }
  else
  {
    printf("Arquivo não especificado.\n");
  }   
  return 0;
}