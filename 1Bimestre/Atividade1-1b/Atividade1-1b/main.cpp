#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>

void display() {
  // Limpa o buffer de cor
  glClear(GL_COLOR_BUFFER_BIT);

  // Define a cor
  glColor3f(0.7, 0.0, 0.0);
  //Tamanho do ponto
  glPointSize(10.0);
  // Desenhando a ponta da espada
  glBegin(GL_POINTS);
    glVertex2f(0.0, 0.5);
    glVertex2f(0.0, 0.45);
    glVertex2f(0.0, 0.4);
    glVertex2f(0.05, 0.45);
    glVertex2f(0.05, 0.4);
    glVertex2f(0.1, 0.4);
    glVertex2f(-0.05, 0.45);
    glVertex2f(-0.05, 0.4);
  glEnd();

  glColor3f(0.25, 0.25, 0.25);

  //Desenhando o Gume
  glBegin(GL_POINTS);
    for(double j = 0.35; j >= -0.1; j -= 0.05){
        glVertex2f(0.1, j);
        glVertex2f(-0.1, j);
        glVertex2f(0, j);
        glVertex2f(-0.05, j);
        glVertex2f(0.05, j);
    }
    glColor3f(0.4,0.4,0.4);
    glVertex2f(0.1, 0.25);
    glVertex2f(0.1, 0.2);
    glVertex2f(0.1, 0.15);
    glVertex2f(0.1, 0.1);
    glVertex2f(0.1, 0.05);
    glVertex2f(0.1, 0.0);
    glColor3f(0.25, 0.25, 0.25);
    glVertex2f(-0.1, 0.4);

    //sangue da espada
    glColor3f(0.7, 0.0, 0.0);
    glVertex2f(0.05, 0.35);
    glVertex2f(0, 0.35);
    glVertex2f(0, 0.3);
    glVertex2f(-0.05, 0.35);
    glVertex2f(-0.05, 0.3);
    glVertex2f(-0.05, 0.25);
  glEnd();

  glColor3f(0,0,0);

  //Desenhando o guarda mão
  glBegin(GL_POINTS);
    glVertex2f(-0.3, -0.2);
    glVertex2f(0.3, -0.2);
    for(double i = -0.25; i <= 0.0; i+= 0.05){
        glVertex2f(i, -0.15);
        glVertex2f(-i, -0.15);
        glColor3f(0.4, 0.2, 0.0);
        glVertex2f(i, -0.2);
        glVertex2f(-i, -0.2);
        glColor3f(0,0,0);
        glVertex2f(i, -0.25);
        glVertex2f(-i, -0.25);
    }
  glEnd();

  //Desenhando o cabo
  glBegin(GL_POINTS);
  glColor3f(0,0,0);
    for(double j = -0.3; j >= -0.55; j-= 0.05){
        glVertex2f(0.05, j);
        glVertex2f(-0.05, j);
        glVertex2f(0.0, j);
    }
    glVertex2f(0.0, -0.65);
    glVertex2f(0.05, -0.6);
    glVertex2f(-0.05, -0.6);

    //Desenhando o detalhe da espada
    glColor3f(1.0, 0.84, 0.0);
    glVertex2f(0, -0.55);
    glVertex2f(0, -0.6);
  glEnd();

  // Exibe o buffer de cor
  glutSwapBuffers();
}

int main(int argc, char** argv) {
  // Inicializa o GLUT e cria uma janela
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  glutCreateWindow("Espada");

  // Define a cor de fundo para branco
  glClearColor(1, 1, 1, 0);

  // Define a função de exibição
  glutDisplayFunc(display);

  // Entra no loop de eventos do GLUT
  glutMainLoop();

  return 0;
}
