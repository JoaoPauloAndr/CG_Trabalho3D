#include "../includes/game_platforms.h"

bool inRange(GLfloat low, GLfloat high, GLfloat x)
{
    return  (low <= x && x <= high);
}

//GLfloat platformX, GLfloat platformY, GLfloat platformBottom, GLfloat platformBack
void colision(platform_specs specs, Character *charac, bool *prevCol, 
              Enemy *enemies, bool *enemiesColisions, unsigned int n_enemies, int j)
{
    GLfloat platformX = specs.platformX;
    GLfloat platformY = specs.platformY;
    GLfloat platformBottom = specs.platformBottom;
    GLfloat platformBack = specs.platformBack;

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

    //Enemies Colision
    for(int n = 0; n < n_enemies; n++)
    {
        GLfloat enemyFront = enemies[n].getFront();
        GLfloat enemyBack = enemies[n].getBack();
        GLfloat enemyBottom = enemies[n].getY();
        GLfloat enemyTop = enemies[n].getTop();

        //Front colision
        if(enemyFront >= platformX && enemyFront < platformBack 
            && (inRange(platformBottom, platformY, charTop) ||
                inRange(platformBottom, platformY, enemyBottom) ||
                inRange(enemyBottom, enemyTop, platformY)))
        {
            enemiesColisions[n] = true;
            enemies[n].setFrontColision();
        }
        else
        {
            if(!enemiesColisions[n])
                enemies[n].unsetFrontColision();
        }

        //Back colision
        if(enemyBack > platformX && enemyBack <= platformBack 
            && (inRange(platformBottom, platformY, enemyTop) ||
                inRange(platformBottom, platformY, enemyBottom) ||
                inRange(enemyBottom, enemyTop, platformY)))
        {
            enemiesColisions[n] = true;
            enemies[n].setBackColision();
        }
        else
        {
            if(!enemiesColisions[n])
                enemies[n].unsetBackColision();
        }

        //Top colision
        if(enemyTop >= platformBottom && enemyTop < platformY 
        && (inRange(platformX, platformBack, enemyFront) &&
            inRange(platformX, platformBack, enemyBack)))
        {
            enemiesColisions[n] = true;
            enemies[n].setTopColision();
        }
        else
        {
            if(!enemiesColisions[n])
                enemies[n].unsetTopColision();
        }

        //Bottom colision
        if(enemyBottom <= platformY && enemyBottom > platformBottom 
        && (inRange(platformX, platformBack, enemyFront) &&
            inRange(platformX, platformBack, enemyBack)))
        {
            enemiesColisions[n] = true;
            enemies[n].setBottomColision(j);
            enemies[n].setNewGY(platformY+0.01);
        }
        else
        {
            if(!enemiesColisions[n] && !(inRange(platformX, platformBack, enemies[n].getX())))
                enemies[n].unsetBottomColision(j);
        }

        //shots colision
        unsigned int validShots_len = enemies[n].getValidShotsSize();
        unsigned int shots[validShots_len]; 
        enemies[n].getValidShots(shots);
        GLfloat x, y, z;
        
        for(int i = 0; i < validShots_len; i++)
        {
            enemies[n].getShotPos(shots[i], x, y, z);
            if(inRange(platformX, platformBack, x) &&
            inRange(platformBottom, platformY, y))
            {
                enemies[n].invalidateShot(shots[i]);
            }   
        }
    }    
}

void drawPlatforms(Platforms platforms, GLfloat arenaWidth, Character *player, Enemy *enemies, unsigned int n_enemies)
{
    bool previousColision = false;
    bool enemiesColisions[n_enemies] = {false};
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

        platform_specs specs = {platformX, platformY, platformY - platformHeight, platformX + platformWidth};

        colision(specs, player, &previousColision, enemies, enemiesColisions, n_enemies, j);
        j++;
    }
}