#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy: public Character
{
    using Character::Character;
    private:
       void DrawHead(GLfloat head_radius) override;
    //public:   
};
#endif