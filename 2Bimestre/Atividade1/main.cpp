#include <iostream>
#include <GL/glut.h>
#include <list> 
#include <math.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Ponto {
private:
    float x;
    float y;
    float z;
public:
    Ponto(float a, float b, float c) {
        x = a;
        y = b;
        z = c;
    }
    float getX() {
        return x;
    }
    float getY() {
        return y;
    }
    float getZ() {
        return z;
    }
    void setX(float a) {
        x = a;
    }
    void setY(float b) {
        y = b;
    }
    void setZ(float c) {
        z = c;
    }
};

list<Ponto> vertices;
list<list<Ponto>> listaFaces;
list<int> indiceFace;
list<list<int>> listaIndice;
int centroMassaX, centroMassaY, centroMassaZ;

void openFile() {
    std::ifstream inFile("C:/Users/Cassio/Desktop/a.obj");

    if (!inFile)
    {
        std::cerr << "Erro de arquivo! " << std::endl;
        return;
    }
    std::string line;
    string v, x, y, z;
    string f, n1, n2, n3, n4;
    while (std::getline(inFile, line)) { // percorre cada linha do arquivo
        if (line.size() > 0 && line[0] != '#') { //verifica se é um comentário
            if (line[0] == 'v') { //pegando os vertices
                std::istringstream iss(line);
                iss >> v >> x >> y >> z;
                vertices.push_back(Ponto(stof(x), stof(y), stof(z))); //adicionando na lista de vertices
            }
            else if (line[0] = 'f') { //pegando as faces
                indiceFace.clear();
                std::istringstream iss(line);
                iss >> f >> n1 >> n2 >> n3 >> n4;
                indiceFace.push_back(stoi(n1));
                indiceFace.push_back(stoi(n2));
                indiceFace.push_back(stoi(n3));
                indiceFace.push_back(stoi(n4));
                listaIndice.push_back(indiceFace); //colocando na lista as faces para desenhar
            }
        }
    }
    listaFaces.push_back(vertices); //adicionando os vertices que compõem a face
    inFile.close();
}

void calculaCentroMassa() {//percorre os vertices da face e faz o calculo do centro da massa
    float somaX = 0, somaY = 0, somaZ = 0;
    int totalPontos = 0;
    for (auto it = listaIndice.begin(); it != listaIndice.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            for (auto it3 = listaFaces.begin(); it3 != listaFaces.end(); it3++) {
                for (auto it4 = it3->begin(); it4 != it3->end(); it4++) {
                    if (std::distance(it3->begin(), it4) + 1 == *it2) {
                        somaX += it4->getX();
                        somaY += it4->getY();
                        somaZ += it4->getZ();
                        totalPontos++;
                    }
                }
            }
        }
    }
    centroMassaX = somaX / totalPontos;
    centroMassaY = somaY / totalPontos;
    centroMassaZ = somaZ / totalPontos;
}

void rotateX(float angulo) { //percorre os vertices e aplica a formula da rotação no eixo X
    for (auto it = listaIndice.begin(); it != listaIndice.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            for (auto it3 = listaFaces.begin(); it3 != listaFaces.end(); it3++) {
                for (auto it4 = it3->begin(); it4 != it3->end(); it4++) {
                    if (std::distance(it3->begin(), it4) + 1 == *it2) {
                        float x = it4->getX() + centroMassaX;
                        float y = (it4->getY() - centroMassaY) * cos(angulo) - (it4->getZ() - centroMassaZ) * sin(angulo) + centroMassaY;
                        float z = (it4->getY() - centroMassaY) * sin(angulo) + (it4->getZ() - centroMassaZ) * cos(angulo) + centroMassaZ;
                        it4->setX(x);
                        it4->setY(y);
                        it4->setZ(z);
                    }
                }
            }
        }
    }
}

void rotateY(float angulo) {//percorre os vertices e aplica a formula da rotação no eixo Y
    for (auto it = listaIndice.begin(); it != listaIndice.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            for (auto it3 = listaFaces.begin(); it3 != listaFaces.end(); it3++) {
                for (auto it4 = it3->begin(); it4 != it3->end(); it4++) {
                    if (std::distance(it3->begin(), it4) + 1 == *it2) {
                        float y = it4->getY() + centroMassaY;
                        float x = (it4->getZ() - centroMassaZ) * cos(angulo) - (it4->getX() - centroMassaX) * sin(angulo) + centroMassaX;
                        float z = (it4->getZ() - centroMassaZ) * sin(angulo) + (it4->getX() - centroMassaX) * cos(angulo) + centroMassaZ;
                        it4->setX(x);
                        it4->setY(y);
                        it4->setZ(z);
                    }
                }
            }
        }
    }
}

void rotateZ(float angulo) { //percorre os vertices e aplica a formula da rotação no eixo Z
    for (auto it = listaIndice.begin(); it != listaIndice.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            for (auto it3 = listaFaces.begin(); it3 != listaFaces.end(); it3++) {
                for (auto it4 = it3->begin(); it4 != it3->end(); it4++) {
                    float z = it4->getZ() + centroMassaZ;
                    float x = (it4->getX() - centroMassaX) * cos(angulo) - (it4->getY() - centroMassaX) * sin(angulo) + centroMassaX;
                    float y = (it4->getX() - centroMassaX) * sin(angulo) + (it4->getY() - centroMassaX) * cos(angulo) + centroMassaY;
                    it4->setX(x);
                    it4->setY(y);
                    it4->setZ(z);
                }
            }
        }
    }
}

void controleEscala(float taxaEscala) { //percorre todos os vertices e aplica a escala desejada.
    float tamanhoEscala = 1;
    tamanhoEscala += taxaEscala;
    for (auto it = listaIndice.begin(); it != listaIndice.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            for (auto it3 = listaFaces.begin(); it3 != listaFaces.end(); it3++) {
                for (auto it4 = it3->begin(); it4 != it3->end(); it4++) {
                    float x = (it4->getX() - centroMassaX) * tamanhoEscala + centroMassaX;
                    float y = (it4->getY() - centroMassaY) * tamanhoEscala + centroMassaY;
                    float z = (it4->getZ() - centroMassaZ) * tamanhoEscala + centroMassaZ;
                    it4->setX(x);
                    it4->setY(y);
                    it4->setZ(z);
                }
            }
        }
    }
}

void transladar(float taxaX, float taxaY, float taxaZ) { //percorre todos os vertices e aplica a taxa de translação desejada.
    for (auto it = listaIndice.begin(); it != listaIndice.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            for (auto it3 = listaFaces.begin(); it3 != listaFaces.end(); it3++) {
                for (auto it4 = it3->begin(); it4 != it3->end(); it4++) {
                    float x = it4->getX() + taxaX;
                    float y = it4->getY() + taxaY;
                    float z = it4->getZ() + taxaZ;
                    it4->setX(x);
                    it4->setY(y);
                    it4->setZ(z);
                }
            }
        }
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    for (auto it = listaIndice.begin(); it != listaIndice.end(); it++) {//percorrendo a quantidade de faces (6)
        glBegin(GL_LINE_STRIP);
        for (auto it2 = it->begin(); it2 != it->end(); it2++) { //percorre as faces  do desenho (24)
            for (auto it3 = listaFaces.begin(); it3 != listaFaces.end(); it3++) { //percorrendo quais faces devem ser desenhadas
                for (auto it4 = it3->begin(); it4 != it3->end(); it4++) { //percorrendo os vertices da face
                    float x, y, z;
                    if (std::distance(it3->begin(), it4) + 1 == *it2) { // se a face deve ser desenhada
                        x = it4->getX(); //pega os valores do vertice
                        y = it4->getY();
                        z = it4->getZ();
                        glColor3f(0.0, 1.0, 0.0);
                        glVertex3d(x, y, z); // desenha os vertices
                    }

                }
            }
        }
        glEnd();
    }
    glFlush();
}

void teclado(unsigned char key, int x, int y) {
    switch (key)
    {
    case 'x':
        rotateX(90);
        break;
    case 'y':
        rotateY(90);
        break;
    case 'z':
        rotateZ(90);
        break;
    case 'e':
        controleEscala(0.01);
        break;
    case 'q':
        controleEscala(-0.01);
        break;
    case 'w':
        transladar(0, 0.01, 0);
        break;
    case 's':
        transladar(0, -0.01, 0);
        break;
    case 'a':
        transladar(-0.01, 0, 0);
        break;
    case 'd':
        transladar(0.01, 0, 0);
        break;
    case 'k':
        transladar(0, 0, -0.01);
    case 'l':
        transladar(0, 0, 0.01);
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    openFile();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Cubo!");
    glOrtho(-2, 2, -2, 2, -10, 10);
    glutKeyboardFunc(teclado);
    glutDisplayFunc(display);
    calculaCentroMassa();
    glutMainLoop();
    return 0;
}