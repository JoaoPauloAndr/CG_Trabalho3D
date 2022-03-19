#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <random>
#include <bits/stdc++.h>
#include "shot.h"

#define ARM_ANGLE_LIMIT     45
#define SCALE               0.75
#define VEL                 0.75
#define INC_DY              3
#define JUMP_COUNTER_MAX    1.0//20
#define GRAVITY             0.7
#define INC_DIRECTION       3
#define LEG_ANGLE_UP_LIMIT  35
#define LEG_ANGLE_LO_LIMIT -30
#define INC_ANGLE           3
#define INC_ANGLE_UP_LEG    2
#define BULLET_QTY          10

class Character
{
    GLfloat gX;
    GLfloat gY;
    GLfloat gZ;
    GLfloat head_radius;
    GLfloat arenaLength;
    GLfloat arenaWidth;
    GLfloat loLegLength;
    GLfloat loLegWidth;
    GLfloat loLegHeight;
    GLfloat upLegLength;
    GLfloat upLegWidth;
    GLfloat upLegHeight;
    GLfloat torsoLength;
    GLfloat torsoWidth; 
    GLfloat torsoHeight;
    GLfloat armLength;
    GLfloat armWidth;  
    GLfloat armHeight;
    GLfloat armTheta;
    GLdouble direction;
    GLfloat upperLegAngle;
    GLfloat upperLegDelta;
    GLfloat gravityCounter;
    GLfloat jumpCounter;
    //Character colors
    GLfloat headEmission[4];
    GLfloat headColor[4];
    GLfloat torsoEmission[4];
    GLfloat torsoColor[4];
    GLfloat legEmission[4];
    GLfloat legColor[4];
    //GLfloat[4] headColor;
    Shot    shots[BULLET_QTY];
    unsigned int shots_fired;
    std::list<unsigned int> validShots;
    bool frontColision;
    bool backColision;
    bool topColision;
    bool bottomColision;
    int platformID;
    bool idle;
    bool running;
    bool isGrounded;
    bool isJumping;
private:
    void DrawCharacter(GLfloat gX, GLfloat gY, GLfloat head_radius);
    virtual void DrawHead(GLfloat head_radius);
    void DrawLegs();
    void DrawLeftLeg();
    void DrawRightLeg();
    void DrawTorso();
    void DrawArms();
    void DrawRightArm();
    void DrawLeftArm();   
    void MoveX(GLfloat dx);
    void restoreGroundedStatus();
    void drawShot();
public:
    Character()
    : headEmission{0.00, 0.25, 0.00, 1},
      headColor{ 0.0, 1.0, 0.0, 1},
      torsoEmission{ 0.6, 0.6, 0.6, 1},
      torsoColor{ 1.0, 1.0, 1.0, 1},
      legEmission{ 0.12, 0.20, 0.35, 1},
      legColor{ 0.2, 0.56, 1, 1}
    {
        gX          = 0;
        gY          = 0;
        head_radius = 0;
        loLegLength = 0;
        loLegWidth  = 0;
        loLegHeight = 0;
        upLegLength = 0;
        upLegWidth  = 0;
        upLegHeight = 0;
        torsoLength = 0;  
        torsoWidth  = 0; 
        torsoHeight = 0;
        armLength   = 0;
        armWidth    = 0;
        armHeight   = 0;
        armTheta    = 0;
        direction   = 0;
        upperLegAngle = 0;
        upperLegDelta = INC_ANGLE_UP_LEG;
        gravityCounter = 0;
        jumpCounter = JUMP_COUNTER_MAX;
        shots_fired = 0;
        frontColision = false;
        backColision = false;
        topColision = false;
        bottomColision = false;
        idle = true;
        running = false;
        isGrounded = true;
        isJumping = false;
        platformID = -1;
    };

    void Draw()
    {
        DrawCharacter(gX, gY, head_radius);
    };

    virtual void Init(GLfloat x, GLfloat length, GLfloat width, GLfloat radius)
    {   
        gX = x;
        gY = 0; //y
        //generate random value to set as gZ
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_real_distribution<> distr(10, width-10); // define the range
        gZ = distr(gen);
        arenaWidth = width;
        arenaLength = length;
        head_radius = (SCALE - 0.45) * radius;
        loLegLength = SCALE * 0.5 * head_radius;
        loLegWidth = SCALE * loLegLength;
        loLegHeight = SCALE * 2 * head_radius;
        upLegLength = SCALE * 0.8 * head_radius;
        upLegWidth = SCALE * 0.8 * head_radius;
        upLegHeight = SCALE * 2.2 * head_radius;
        torsoLength = SCALE * head_radius;
        torsoWidth = SCALE * 2.3 * head_radius;
        torsoHeight = SCALE * 3 * head_radius;
        armLength = SCALE * 0.5 * head_radius;
        armWidth = SCALE * armLength;
        armHeight = SCALE * 2.2 * head_radius;
        //for re initialization
        direction   = 0;
        upperLegAngle = 0;
        upperLegDelta = INC_ANGLE_UP_LEG;
        gravityCounter = 0;
        jumpCounter = JUMP_COUNTER_MAX;
        shots_fired = 0;
        frontColision = false;
        backColision = false;
        topColision = false;
        bottomColision = false;
        idle = true;
        running = false;
        isGrounded = true;
        isJumping = false;
        platformID = -1;
    };

    virtual void Init(GLfloat x, GLfloat y, GLfloat length, GLfloat width, GLfloat radius)
    {   
        gX = x;
        gY = y - radius;
        //generate random value to set as gZ
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_real_distribution<> distr(10, width-10); // define the range
        gZ = distr(gen);
        arenaWidth = width;
        arenaLength = length;
        head_radius = (SCALE - 0.45) * radius;
        loLegLength = SCALE * 0.5 * head_radius;
        loLegWidth = SCALE * loLegLength;
        loLegHeight = SCALE * 2 * head_radius;
        upLegLength = SCALE * 0.8 * head_radius;
        upLegWidth = SCALE * 0.8 * head_radius;
        upLegHeight = SCALE * 2.2 * head_radius;
        torsoLength = SCALE * head_radius;
        torsoWidth = SCALE * 2.3 * head_radius;
        torsoHeight = SCALE * 3 * head_radius;
        armLength = SCALE * 0.5 * head_radius;
        armWidth = SCALE * armLength;
        armHeight = SCALE * 2.2 * head_radius;
        //for re initialization
        direction   = 0;
        upperLegAngle = 0;
        upperLegDelta = INC_ANGLE_UP_LEG;
        gravityCounter = 0;
        jumpCounter = JUMP_COUNTER_MAX;
        shots_fired = 0;
        frontColision = false;
        backColision = false;
        topColision = false;
        bottomColision = false;
        idle = true;
        running = false;
        isGrounded = true;
        isJumping = false;
        platformID = -1;
    };

    void HandleInput(bool isRunning, GLfloat vel);

    //void MoveX(GLfloat dx);

    void MoveY(GLfloat dy);

    void RotateZ(GLfloat ang);

    GLfloat getX()
    {
        return gX;
    };

    GLfloat getY()
    {
        return gY;
    };

    GLfloat getZ()
    {
        return gZ;
    };

    GLfloat getCenterY()
    {
        return (gY + loLegHeight + upLegHeight + 0.5 * torsoHeight);
    };

    GLfloat getEyesY()
    {
        return (gY + loLegHeight + upLegHeight + torsoHeight + head_radius);
    };

    GLfloat getEyesX()
    {
        return (gX + head_radius * cos(direction * M_PI/180));
    };

    GLfloat getEyesZ()
    {
        return (gZ + head_radius * (-1) * sin(direction * M_PI/180));
    };

    GLfloat getFront()
    {
        return (gX + (0.5) * armHeight * cos(direction * M_PI/180));
    };

    GLfloat getBack()
    {
        return (gX + (-0.5) * armHeight * cos(direction * M_PI/180));
    };

    GLfloat getTop()
    {
        return (gY + loLegHeight + upLegHeight + torsoHeight + 2 * head_radius);
    };

    GLfloat getRightArmX()
    {
        return gX + ((0.5) * armHeight * cos(direction * M_PI/180) * cos(armTheta * M_PI/180)) + (((0.5) * armHeight + 0.5 * armLength) * sin(direction * M_PI/180));
    };

    GLfloat getRightArmY()
    {
        return gY + loLegHeight + upLegHeight + torsoHeight + armLength + ((0.5 * armHeight) * sin(armTheta*M_PI/180)); //- head_radius  + (sin(armTheta*M_PI/180));
    };

    GLfloat getRightArmZ()
    {
        return gZ + ((0.5 * torsoWidth + 0.5 * armWidth) * cos(direction * M_PI/180)) + ((0.5 * armHeight) * (-1) * sin(direction * M_PI/180) * cos(armTheta * M_PI/180));
    };

    GLfloat getWeaponX()
    {
        return gX + ((armHeight + SHOT_RADIUS) * cos(direction * M_PI/180) * cos(armTheta * M_PI/180)) + ((0.5 * torsoWidth + 0.5 * armWidth) * sin(direction * M_PI/180));
    };

    GLfloat getWeaponY()
    {
        return gY + loLegHeight + upLegHeight + torsoHeight - (0.5 * armLength) + ((armHeight + SHOT_RADIUS) * sin(armTheta * M_PI/180)); //
    };

    GLfloat getWeaponZ()
    {
        return gZ + ((0.5 * torsoWidth + SHOT_RADIUS) * cos(direction * M_PI/180)) + ((armHeight + SHOT_RADIUS)  * (-1) * sin(direction * M_PI/180) * cos(armTheta * M_PI/180));
    };

    GLfloat getDiretion()
    {
        return (GLfloat) direction;
    };

    GLfloat getArmTheta()
    {
        return armTheta;
    };

    void moveArm(GLfloat inc);

    bool isRunning()
    {
        return running;
    };

    void setFrontColision()
    {
        frontColision = true;
    };

    void unsetFrontColision()
    {
        frontColision = false;
    };

    void setBackColision()
    {
        backColision = true;
    };

    void unsetBackColision()
    {
        backColision = false;
    };

    void setTopColision()
    {
        topColision = true;
    };

    void unsetTopColision()
    {
        topColision = false;
    };

    void setBottomColision(int id)
    {
        platformID = id;
        bottomColision = true;
        isGrounded = true;
        isJumping = false;
    };

    void unsetBottomColision(int id);

    void setNewGY(GLfloat newGY)
    {
        gY = newGY;
    };

    bool getIsGrounded()
    {
        return isGrounded;
    };

    void Jump();

    bool getIsJumping()
    {
        return isJumping;
    };

    GLfloat getJumCounter()
    {
        return jumpCounter;
    };

    void resetJump()
    {
        isJumping = 0;
        jumpCounter = JUMP_COUNTER_MAX;
    };

    void Shoot();

    void invalidateShot(unsigned int i)
    {
        validShots.remove(i);
        shots_fired = validShots.size();
    };

    bool checkBulletValidity(unsigned int i)
    {
        return shots[i].checkValidity();
    };

    void drawBullet(unsigned int i)
    {
        shots[i].Draw();
    };

    void moveBullet(unsigned int i)
    {
        shots[i].Move();
    };

    unsigned int getValidShotsSize()
    {
        return validShots.size();
    };

    void getValidShots(unsigned int *arr);

    void getShotPos(unsigned int i, GLfloat &x, GLfloat &y, GLfloat &z)
    {   
        shots[i].getPos(x, y, z);    
    };

    //For enemy setup
    void setDirection(GLdouble dir)
    {
        direction += dir;
    };

    // void setHeadColor(GLfloat arr[4])
    // {
    //     headColor = arr;
    // };
};
#endif