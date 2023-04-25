#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

int mouseX, mouseY;
bool flag = false;
int raio = 50;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    if (flag)
    { // se o mouse foi clicado, inicia o desenho
        glBegin(GL_LINE_STRIP);
        glVertex2f(mouseX, -90 + mouseY); // Primeira linha da teardrop
        double angulo = 0;
        for (double i = 0; i <= 7000; i++)
        {
            glVertex2i(mouseX + raio * cos(angulo), mouseY + raio * sin(angulo)); // desenhando o circulo
            angulo = i * (M_PI / 7000);                                           // faz um meio circulo, convertendo para radianos o angulo é 180 graus.
        }

        glVertex2f(mouseX, -90 + mouseY); // desenha a segunda linha da teardrop

        glEnd();
    }

    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseX = x;
        mouseY = y;
        flag = true;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Atividade 04/1");
    gluOrtho2D(0, 500, 500, 0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}