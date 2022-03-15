#ifndef SHOT_H
#define SHOT_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define SHOT_RADIUS         0.2

class Shot
{
    GLfloat gXInit; 
    GLfloat gYInit;
    GLfloat gZInit; 
    GLfloat gX; 
    GLfloat gY;
    GLfloat gZ; 
    GLfloat gDirection;
    GLfloat gTheta;
    GLfloat gvel;
    unsigned int id;
    bool    valid;

private:
    //void DrawCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawShot(GLfloat x, GLfloat y, GLfloat z);

public:
    Shot()
    {
        gXInit = 0;
        gYInit = 0;
        gZInit = 0;
        gX = 0;
        gY = 0;
        gZ = 0;
        gDirection = 0;
        gTheta = 0;
        gvel = 0;
        valid = false;
        id = 0;
    };

    void Shot_Init(GLfloat x, GLfloat y, GLfloat z, GLfloat direction, GLfloat theta, GLfloat vel, int i){
        gXInit = x;
        gYInit = y;
        gZInit = z;
        gX = x;
        gY = y;
        gZ = z;
        gDirection = direction;
        gTheta = theta;
        gvel = vel;
        valid = true;
        id = i;
    };

    void Draw(){
        DrawShot(gX, gY, gZ);
    };

    void Move();

    void Invalidate(){
        valid = false;
    };

    bool checkValidity(){
        return valid;
    };

    void getPos(GLfloat &xOut, GLfloat &yOut, GLfloat &zOut){
        xOut = gX;
        yOut = gY;
        zOut = gZ;
    };

    int getId()
    {
        return id;
    };
};

#endif
