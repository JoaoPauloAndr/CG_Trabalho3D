#include "../includes/enemy.h"

void Enemy::DrawHead(GLfloat head_radius)
{
    glShadeModel(GL_SMOOTH);

    GLfloat materialEmission[] = { 0.25, 0.00, 0.00, 1};
    GLfloat materialColor[] = { 1.0, 0.0, 0.0, 1};
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