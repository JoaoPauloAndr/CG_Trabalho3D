#ifndef GAME_PLATFORMS_H
#define GAME_PLATFORMS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "info.h"
#include "character.h"
#include "enemy.h"

struct platform_specs
{
    GLfloat platformX;
    GLfloat platformY;
    GLfloat platformBottom;
    GLfloat platformBack;
};

void drawPlatforms(Platforms platforms, GLfloat arenaWidth, Character *player, Enemy *enemies, unsigned int n_enemies); //std::vector<Platform> Platforms

#endif