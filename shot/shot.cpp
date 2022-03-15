#include "../includes/shot.h"

void Shot::DrawShot(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glShadeModel(GL_SMOOTH);

    GLfloat materialEmission[] = { 1.00, 0.25, 0.00, 1};
    GLfloat materialColor[] = { 1.0, 1.0, 0.0, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = { 50.0 };
    glColor3f(0,1,0);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere(SHOT_RADIUS, 20, 10);

    glPopMatrix();
}

void Shot::Move()
{
    GLfloat xInc = (gvel * SHOT_RADIUS * cos(gDirection * M_PI/180) * cos(gTheta * M_PI/180)) + (gvel * SHOT_RADIUS * sin(gDirection * M_PI/180));
    GLfloat yInc = gvel * SHOT_RADIUS * sin(gTheta * M_PI/180);
    GLfloat zInc = (gvel * SHOT_RADIUS * cos(gDirection * M_PI/180)) + (gvel * SHOT_RADIUS * (-1) * sin(gDirection * M_PI/180) * cos(gTheta * M_PI/180));

    gX += xInc;
    gY += yInc;
    gZ += zInc;

}