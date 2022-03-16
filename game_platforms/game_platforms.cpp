#include "../includes/game_platforms.h"

bool inRange(GLfloat low, GLfloat high, GLfloat x)
{
    return  (low <= x && x <= high);
}

void colision(GLfloat platformX, GLfloat platformY, GLfloat platformBottom, GLfloat platformBack, Character *charac, bool *prevCol, int j)
{
    GLfloat charFront = charac->getFront();
    GLfloat charBack = charac->getBack();
    GLfloat charBottom = charac->getY();
    GLfloat charTop = charac->getTop();

    //Front colision
    if(charFront >= platformX && charFront < platformBack 
        && (inRange(platformBottom, platformY, charTop) ||
            inRange(platformBottom, platformY, charBottom) ||
            inRange(charBottom, charTop, platformY)))
    {
        *prevCol = true;
        charac->setFrontColision();
    }
    else
    {
        if(!*prevCol)
            charac->unsetFrontColision();
    }

    //Back colision
    if(charBack > platformX && charBack <= platformBack 
        && (inRange(platformBottom, platformY, charTop) ||
            inRange(platformBottom, platformY, charBottom) ||
            inRange(charBottom, charTop, platformY)))
    {
        *prevCol = true;
        charac->setBackColision();
    }
    else
    {
        if(!*prevCol)
            charac->unsetBackColision();
    }

    //Top colision
    if(charTop >= platformBottom && charTop < platformY 
    && (inRange(platformX, platformBack, charFront) &&
        inRange(platformX, platformBack, charBack)))
    {
        *prevCol = true;
        charac->setTopColision();
    }
    else
    {
        if(!*prevCol)
            charac->unsetTopColision();
    }

    //Bottom colision
    if(charBottom <= platformY && charBottom > platformBottom 
    && (inRange(platformX, platformBack, charFront) &&
        inRange(platformX, platformBack, charBack)))
    {
        *prevCol = true;
        charac->setBottomColision(j);
        charac->setNewGY(platformY+0.01);
    }
    else
    {
        if(!*prevCol && !(inRange(platformX, platformBack, charac->getX())))
            charac->unsetBottomColision(j);
    }

    //shots colision
    unsigned int validShots_len = charac->getValidShotsSize();
    unsigned int shots[validShots_len]; 
    charac->getValidShots(shots);
    GLfloat x, y, z;
    
    for(int i = 0; i < validShots_len; i++)
    {
        charac->getShotPos(shots[i], x, y, z);
        if(inRange(platformX, platformBack, x) &&
           inRange(platformBottom, platformY, y))
        {
            charac->invalidateShot(shots[i]);
        }   
    }    
}

void drawPlatforms(Platforms platforms, GLfloat arenaWidth, Character *player)
{
    bool previousColision = false;
    int j = 0;
    GLfloat materialEmission[] = { 0.15, 0.15, 0.00, 1.0};
    GLfloat materialColor[] = { 1.0, 1.0, 0.0, 1.0};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = { 128 };
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    for(auto i: platforms)
    {
        GLfloat platformX = i.origin.x;
        GLfloat platformY = i.origin.y;
        GLfloat platformWidth = i.width;
        GLfloat platformHeight = i.height;

        glPushMatrix();

        glTranslatef(platformX + platformWidth/2, platformY - platformHeight/2, arenaWidth/2);
        glScalef(platformWidth, platformHeight, arenaWidth);
        glutSolidCube(1);

        glPopMatrix();

        colision(platformX, platformY, platformY - platformHeight, platformX + platformWidth, player, &previousColision, j);
        j++;
    }
}