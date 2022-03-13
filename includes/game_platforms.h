#ifndef GAME_PLATFORMS_H
#define GAME_PLATFORMS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "info.h"
#include "character.h"

void drawPlatforms(Platforms platforms, GLfloat arenaWidth, Character *player); //std::vector<Platform> Platforms

#endif