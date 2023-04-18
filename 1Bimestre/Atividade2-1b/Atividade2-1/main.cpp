#include <iostream>
#include <GL/glut.h>
#include <list> 
#include <math.h>
#include <cmath>

using namespace std;

struct PONTO {int x; int y;}; //Registro "PONTO", onde ficará armazenado as coordenadas do ponto clicado.

list<PONTO> pontos; //Lista do tipo "Ponto", onde será armazenado todos os pontos clicados.

double funcaoEuclidiana(int x1, int y1, int x2, int y2){ //Função que determina a menor distância entre dois pontos.
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); //formula da distância euclidiana
}

void excluirLinha(int x, int y){
    auto menorDistancia = INFINITY; //Atribui a menor distancia ao infinito na primeira inicialização.
    auto pontoProximo = pontos.begin(); // Toma como base o primeiro ponto como o mais proximo.
    for(auto ponto = pontos.begin(); ponto != pontos.end(); ponto++){ //Percorrendo a lista
        double temp = funcaoEuclidiana(x, y, ponto->x, ponto->y); // atribui o retorno da função euclidiana
        if(temp < menorDistancia){ // se a distancia do ponto atual for menor
            menorDistancia = temp; // a menor distancia é atribuida a esse ponto atual
            pontoProximo = ponto; // o ponto mais proximo é atualizado com o ponto atual
        }
    }
    pontos.erase(pontoProximo); //faz a exclusão do ponto mais próximo.
}

void mouse(int botao, int estado, int x, int y) {
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){ //Se o clique foi no botão esquerdo e o estado do botão está para baixo
        pontos.push_back({x, y}); //Adiciona o ponto na lista passando as coordenadas xy.
    } else if (botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN){ //Se o clique foi no botão direito e o estado do botão está para baixo
        excluirLinha(x, y); //chama a função para excluir a linha
    } else {
        return;
    }
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP); //GL_LINE_STRIP permite desenhar linhas conectadas a partir de pontos.
    glColor3f(1.0, 1.0, 1.0); // Define cor das linhas para branco
    for (auto ponto = pontos.begin();  ponto != pontos.end(); ponto++){ //Enquanto não percorrer todos os elementos da lista
        glVertex2f((double)ponto->x, (double)ponto->y); //Passando as coordenadas de cada ponto, o OpenGL vai conectando as linhas.
    }
    glEnd();
    glFlush();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Atividade 1 - Linhas");
    gluOrtho2D(0, 800, 600, 0);
    glutMouseFunc(mouse); //Função do Mouse
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}