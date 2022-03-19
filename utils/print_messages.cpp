#include "../includes/print_messages.h"

void printWonGame(GLfloat playerX, GLfloat playerY, GLfloat playerZ)
{
    glColor3f(1.0, 1.0, 1.0);
    char str[50] = {};
    strcat(str, "Voce venceu! Pressione 'r' para recomecar.\0");
    glRasterPos3f(playerX, playerY + 10, playerZ);
    char *tmpStr = str;
    while( *tmpStr ){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *tmpStr);
        tmpStr++;
    }
}