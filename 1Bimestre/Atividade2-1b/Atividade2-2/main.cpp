#include <iostream>
#include <GL/glut.h>
#include <list>
#include <math.h>
#include <cmath>

using namespace std;

struct PONTO
{
    int x;
    int y;
}; // Registro "PONTO", onde ficará armazenado as coordenadas do ponto clicado.

list<PONTO> pontos; // Lista do tipo "Ponto", onde será armazenado todos os pontos clicados.

double funcaoEuclidiana(int x1, int y1, int x2, int y2)
{                                                   // Função que determina a menor distância entre dois pontos.
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); // formula da distância euclidiana
}

void pegarPontoProximo(int x, int y)
{
    auto menorDistancia = INFINITY;     // Atribui a menor distancia ao infinito na primeira inicialização.
    auto pontoProximo = pontos.begin(); // Toma como base o primeiro ponto como o mais proximo.
    for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++)
    {                                                             // Percorrendo a lista
        double temp = funcaoEuclidiana(x, y, ponto->x, ponto->y); // atribui o retorno da função euclidiana
        if (temp < menorDistancia)
        {                          // se a distancia do ponto atual for menor
            menorDistancia = temp; // a menor distancia é atribuida a esse ponto atual
            pontoProximo = ponto;  // o ponto mais proximo é atualizado com o ponto atual
        }
    }
    pontos.erase(pontoProximo);                           // faz a exclusão do ponto mais próximo.
    pontos.push_back({pontoProximo->x, pontoProximo->y}); // Adiciona o ponto próximo como o ultimo da lista.
}

void mouse(int botao, int estado, int x, int y)
{
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
    {                             // Se o clique foi no botão esquerdo e o estado do botão está para baixo
        pontos.push_back({x, y}); // Adiciona o ponto na lista passando as coordenadas xy.
    }
    else if (botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
    {                            // Se o clique foi no botão direito e o estado do botão está para baixo
        pegarPontoProximo(x, y); // Chama a função de pegar o ponto mais proximo
    }
    else
    {
        return;
    }
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);       // GL_POINTS para desenhar pontos.
    glColor3f(1.0, 1.0, 1.0); // Define cor dos pontos para branco
    for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++)
    {                                                   // Percorrendo os pontos da lista
        glVertex2f((double)ponto->x, (double)ponto->y); // Desenhando os pontos na tela
    }
    glEnd();
    glFlush();
}

void keyboard(int key, int x, int y)
{
    auto ultimoPonto = pontos.back(); // pega o ultimo ponto
    switch (key)
    {
    case GLUT_KEY_UP:
        ultimoPonto.y -= 10; // Movendo o ponto
        break;
    case GLUT_KEY_DOWN:
        ultimoPonto.y += 10;
        break;
    case GLUT_KEY_RIGHT:
        ultimoPonto.x += 10;
        break;
    case GLUT_KEY_LEFT:
        ultimoPonto.x -= 10;
        break;
    }
    pontos.back() = ultimoPonto; // Atualiza o ponto com as novas coordenadas
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Atividade 1 - Linhas");
    gluOrtho2D(0, 800, 600, 0);
    glPointSize(10.0);         // Define o tamanho do ponto
    glutMouseFunc(mouse);      // Função do Mouse
    glutSpecialFunc(keyboard); // Função do teclado
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
