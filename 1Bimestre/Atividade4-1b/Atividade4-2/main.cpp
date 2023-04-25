#include <iostream>
#include <cmath>
#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_STRIP); 

    glColor3f(1.0, 1.0, 1.0);

    // Loop para desenhar a função
    for (float x = -3.14; x <= 3.14; x += 0.1) {
        float y = sin(x); // Função senoidal f(x) = sen(x)
        glVertex2f(x, y); // Desenha o ponto (x, y)
    }

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutCreateWindow("Atividade 04/2 | Função : f(x) = sen(x)");

    glClearColor(0.0, 0.0, 0.0, 0.0);

    gluOrtho2D(-3.14, 3.14, -1.5, 1.5); // Configura a janela de visualização

    glutDisplayFunc(display);

    glutMainLoop(); 

    return 0;
}
