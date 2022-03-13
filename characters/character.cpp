#include "../includes/character.h"

void Character::DrawHead(GLfloat head_radius)
{
    glShadeModel(GL_SMOOTH);

    GLfloat materialEmission[] = { 0.00, 0.25, 0.00, 1};
    GLfloat materialColor[] = { 0.0, 1.0, 0.0, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = { 50.0 };
    glColor3f(0,1,0);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere(head_radius, 20, 10);

    glShadeModel(GL_FLAT);
}

void Character::DrawLeftArm()
{
    glPushMatrix();
        //glRotatef(30, 1, 0, 0);
        glRotatef(30, 1, 0, 1);
        //printf("Left Arm angle = %.2f\n", leftArmAngle);
        glScalef(armLength, armHeight, armWidth);
        glutSolidCube(1);
    glPopMatrix();
}

void Character::DrawRightArm()
{
    glPushMatrix();
        glScalef(armHeight, armLength, armWidth);
        glutSolidCube(1);
    glPopMatrix();
}

void Character::DrawArms()
{   
    glPushMatrix();
        glTranslatef(0, (-0.5) * armHeight, (-0.5) * torsoWidth + (-0.5) * armWidth);
        DrawLeftArm();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, (-0.5) * armLength, 0);
        glRotatef(armTheta, 0, 0, 1);
        glTranslatef( (0.5) * armHeight , 0, (0.5) * torsoWidth + (0.5) * armWidth);
        DrawRightArm();
    glPopMatrix();    

}

void Character::DrawTorso()
{
    glPushMatrix();
        GLfloat materialEmission[] = { 0.6, 0.6, 0.6, 1};
        GLfloat materialColor[] = { 1.0, 1.0, 1.0, 1};
        GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1};
        GLfloat mat_shininess[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glScalef(torsoLength, torsoHeight, torsoWidth);
        glutSolidCube(1);
    glPopMatrix();
}

void Character::DrawLeftLeg()
{
    //Upper Leg
    glPushMatrix();
        glTranslatef(0, loLegHeight + upLegHeight, SCALE * (-0.5) * head_radius);
        glRotatef(-upperLegAngle, 0, 0, 1);
        glTranslatef(0, (-0.5)*upLegHeight, 0);

        GLfloat materialEmission[] = { 0.12, 0.20, 0.35, 1};
        GLfloat materialColor[] = { 0.2, 0.56, 1, 1};
        GLfloat mat_specular[] = { 0.0, 0.5, 0.1, 1};
        GLfloat mat_shininess[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glPushMatrix();
            glScalef(upLegLength, upLegHeight, upLegWidth);
            glutSolidCube(1);
        glPopMatrix();

        //Lower Leg
        glTranslatef(0, (-0.5) * upLegHeight, 0);
        if(upperLegAngle > 0)
        {
            glRotatef(-upperLegAngle, 0, 0, 1);
        }
        else
        {
            glRotatef(upperLegAngle, 0, 0, 1);
        }
        glTranslatef(0, (-0.5) * loLegHeight, 0);
        glPushMatrix();
            glScalef(loLegLength, loLegHeight, loLegWidth);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();    

}

void Character::DrawRightLeg()
{
    //Upper Leg
    glPushMatrix();
        glTranslatef(0, loLegHeight + upLegHeight, SCALE * (0.5) * head_radius);
        glRotatef(upperLegAngle, 0, 0, 1);
        glTranslatef(0, (-0.5)*upLegHeight, 0);

        GLfloat materialEmission[] = { 0.12, 0.20, 0.35, 1};
        GLfloat materialColor[] = { 0.2, 0.56, 1, 1};
        GLfloat mat_specular[] = { 0.0, 0.5, 0.1, 1};
        GLfloat mat_shininess[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

        glPushMatrix();
            glScalef(upLegLength, upLegHeight, upLegWidth);
            glutSolidCube(1);
        glPopMatrix();

        //Lower Leg
        glTranslatef(0, (-0.5) * upLegHeight, 0);
        if(upperLegAngle < 0)
        {
            glRotatef(upperLegAngle, 0, 0, 1);
        }
        else
        {
            glRotatef(-upperLegAngle, 0, 0, 1);
        }
        glTranslatef(0, (-0.5) * loLegHeight, 0);
        glPushMatrix();
            glScalef(loLegLength, loLegHeight, loLegWidth);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();    

}

void Character::DrawLegs()
{
    glPushMatrix();

    DrawLeftLeg();
    DrawRightLeg();

    glPopMatrix();
}

void Character::DrawCharacter(GLfloat gX, GLfloat gY, GLfloat head_radius)
{
    glPushMatrix();

    glTranslatef(gX, gY, gZ);
    glRotated (direction, 0.0, 1.0, 0.0);

    //start drawing from bottom

    //Legs
    DrawLegs();

    //torso
    glTranslatef(0, loLegHeight + upLegHeight + 0.5 * torsoHeight, 0);
    DrawTorso();
    //Arms
    glPushMatrix();
        glTranslatef(0, 0.5 * torsoHeight, 0);
        DrawArms();
    glPopMatrix();
    //Head
    glTranslatef(0, 0.5 * torsoHeight + head_radius, 0);   
    DrawHead(head_radius);

    glPopMatrix();
}

void Character::HandleInput(bool isRunning, GLfloat vel)
{   
    // if(isGrounded)
    // {
    //     printf("Grounded\n");
    // }
    // else
    // {
    //     printf("Not Grounded\n");  
    // }

    //printf("Jump counter = %.2f\n", jumpCounter);
    
    // if(isJumping)
    // {
    //     printf("is Jumping\n");
    // }
    // else
    // {
    //     printf("not Jumping\n");
    // }      
    if(!isGrounded || topColision)
    {
        if(!isJumping)
        {
            //printf("Not jumping!\n");
            gravityCounter += 0.045;
            MoveY(-gravityCounter*GRAVITY);
        }
        //jumpCounter-= 0.1;
    }
    else
    {
        gravityCounter = 0;
        jumpCounter = JUMP_COUNTER_MAX;
    }
    if(isRunning)
    {
        idle = false;
        running = true;
        MoveX(vel);
        //incrementar angulo perna
        upperLegAngle += upperLegDelta;
        if(upperLegAngle <= LEG_ANGLE_LO_LIMIT || upperLegAngle >= LEG_ANGLE_UP_LIMIT)
            upperLegDelta = -upperLegDelta;

        /*leftArmAngle += leftArmDelta;
        if(leftArmAngle <= 0 || upperLegAngle >= LEF_ARM_ANGLE_LIMIT)
            leftArmDelta = -leftArmDelta;*/
    }
    else
    {
        idle = true;
        running = false;
    }
}

void Character::RotateZ(GLfloat ang)
{
    GLdouble dirDbl = direction + ang;
    int dirInt = (int) direction + ang;
    direction = dirInt%360 + (dirDbl - (int)dirInt); 
}

void Character::MoveX(GLfloat dx)
{
    GLfloat dx_x = dx;
    GLfloat dx_z = dx;
    GLfloat cosDir = cos(direction * M_PI/180);
    if((frontColision && dx > 0) || (backColision && dx < 0))
    {
        dx_x = 0;
    }
    else
    {
        backColision = false;
        frontColision = false;
    }
    if((gX <= 0 && cosDir > 0) || (gX >= arenaLength && cosDir < 0))
    {
        dx_x = 0.05*VEL;
    }
    else if((gX <= 0 && cosDir < 0) || (gX >= arenaLength && cosDir > 0))
    {
        dx_x = -0.05*VEL;
    }
    if(gZ <= 0)
    {
        gZ = 0.01;
    }
    if(gZ >= arenaWidth)
    {
        gZ = arenaWidth - 0.01;
    }  
    gX += dx_x * cos(direction * M_PI/180);
    gZ += dx_z * (-1) * sin(direction * M_PI/180);
}

void Character::unsetBottomColision(int id)
{
    if(id == platformID)
    {
        bottomColision = false;
        if(gY <= 0)
        {
            restoreGroundedStatus();
        }
        else
        {
            isGrounded = false;
        }
    }
}

void Character::MoveY(GLfloat dy)
{
    isGrounded = false;
    //GLfloat velY = dy;
    if(topColision && dy > 0 || bottomColision && dy < 0)
    {
        dy = 0; //maybe implement fall() for topColision
    }
    else
    {
        topColision = false;
        bottomColision = false;
    }

    gY += dy;

    if(gY < 0)
    {
        gY = 0;
        restoreGroundedStatus();
    }
    if(bottomColision)
    {
        restoreGroundedStatus();
    }
}

void Character::moveArm(GLfloat angle)
{
    armTheta += angle;
    if(armTheta >= ARM_ANGLE_LIMIT){
        armTheta = ARM_ANGLE_LIMIT;
    }else if(armTheta <= -ARM_ANGLE_LIMIT){
        armTheta = -ARM_ANGLE_LIMIT;
    }    
}

void Character::restoreGroundedStatus()
{
    isGrounded = true;
    //if(jumpCounter < 0){
    isJumping = false;
    jumpCounter = JUMP_COUNTER_MAX;
    //}
}

void Character::Jump()
{
    isJumping = true;
    //isGrounded = false;
    GLfloat jump_val = jumpCounter * INC_DY;
    jumpCounter -= 0.05;
    if(jumpCounter < 0)
    {
        isJumping = false;
        jump_val = 0;
    }
    MoveY(jump_val);
}

// void Character::checkIsGrounded()
// {
//     if(gY <= 0 || )
// }