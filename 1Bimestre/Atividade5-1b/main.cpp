#include <iostream>
#include <GL/glut.h>
#include <list> 
#include <math.h>
#include <cmath>

using namespace std;

struct PONTO { int x; int y; };

list<PONTO> pontos;
double centroX = 800 / 2; //pega o centro da janela horizontalmente
double centroY = 600 / 2; //pega o centro da janela verticalmente
double escalaAumenta = 1; // variavel para aumento da escala
double escalaDiminui = 1; // variavel para diminuição da escala

double funcaoEuclidiana(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void rotacionaDesenho(bool horario) {
    double angulo = M_PI / 2; // angulo 90 graus em radianos
    if (!horario) {
        angulo = -angulo;
    }
    for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++) {
        double x = (ponto->x - centroX) * cos(angulo) - (ponto->y - centroY) * sin(angulo) + centroX; //rotacionando coordenada x com tomando o centro da janela como ponto origem
        double y = (ponto->x - centroX) * sin(angulo) + (ponto->y - centroY) * cos(angulo) + centroY; //rotacionando coordenada y com tomando o centro da janela como ponto origem
        ponto->x = x; //atribuindo as novas coordenadas à variavel do ponto.
        ponto->y = y;
    }
}


void controleEscala(bool aumentar) {
    if (aumentar) {
        escalaAumenta += 0.1; // aumenta a escala (considere que 1 = 100%, então 1.1 = 110%)
        for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++) {
            ponto->x = (ponto->x - centroX) * escalaAumenta + centroX; // atualiza as coordenadas e aumenta a escala de acordo com o meio da janela
            ponto->y = (ponto->y - centroY) * escalaAumenta + centroY;
        }
    }
    else {
        escalaDiminui -= 0.1; // diminui a escala
        for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++) {
            ponto->x = (ponto->x - centroX) * escalaDiminui + centroX; // atualiza as coordenadas e diminui a escala de acordo com o meio da janela
            ponto->y = (ponto->y - centroY) * escalaDiminui + centroY;
        }
    }

    glutPostRedisplay();
}


void excluirLinha(int x, int y) {
    auto menorDistancia = INFINITY;
    auto pontoProximo = pontos.begin();
    for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++) {
        double temp = funcaoEuclidiana(x, y, ponto->x, ponto->y);
        if (temp < menorDistancia) {
            menorDistancia = temp;
            pontoProximo = ponto;
        }
    }
    pontos.erase(pontoProximo);
}

void mouse(int botao, int estado, int x, int y) {
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        pontos.push_back({ x, y });
    }
    else if (botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN) {
        excluirLinha(x, y);
    }
    else {
        return;
    }
    glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y) {
    switch (key)
    {
    case 'r':
        rotacionaDesenho(true);
        break;
    case 'R':
        rotacionaDesenho(false);
        break;
    case 'w':
    case 'W':
        for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++) {
            ponto->y -= 10; // Fazendo com que o desenho vá para cima
        }
        break;
    case 's':
    case 'S':
        for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++) {
            ponto->y += 10; // Vá para baixo
        }
        break;
    case 'a':
    case 'A':
        for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++) {
            ponto->x -= 10; //vá para o lado esquerdo
        }
        break;
    case 'd':
    case 'D':
        for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++) {
            ponto->x += 10; // vá para o lado direito
        }
        break;
    case 'e':
        controleEscala(true); // chama o controlador de escala passando "true", que significa que é para aumentar
        break;
    case 'E':
        controleEscala(false);// "false" indica para a escala diminuir
        break;
    }
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
    glPointSize(10);
    glColor3f(1.0, 1.0, 1.0);
    for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++) {
        glVertex2f((double)ponto->x, (double)ponto->y);
    }
    glEnd();
    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Atividade 5 - 1 Bimestre");

    gluOrtho2D(0, 800, 600, 0);
    glutMouseFunc(mouse); //Função do Mouse
    glutKeyboardFunc(teclado);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}