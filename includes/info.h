#ifndef INFO_H
#define INFO_H

#include <GL/gl.h>
#include <stdlib.h>
#include <vector>

#define WINDOW_SIZE 500

struct Point
{
  GLfloat x;
  GLfloat y;
};

struct Arena
{
    Point origin;
    GLfloat height;
    GLfloat length; 
    GLfloat width;
};

struct Platform
{
  Point origin;
  float height;
  float width;
};

typedef std::vector<Platform> Platforms;

struct Character_info
{
  Point starting_point;
  GLfloat head_radius;
};

typedef std::vector<Character_info> Enemies_info;


#endif