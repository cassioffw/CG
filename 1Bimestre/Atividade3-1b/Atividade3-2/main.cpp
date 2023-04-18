#include <iostream>
#include <fstream>
#include <list>
#include <GL/glut.h>

struct Point
{
    float x;
    float y;
};

std::list<Point> pontos;

void openFile()
{
    std::ifstream inFile("C:/Users/Cassio/Desktop/dino.Dat"); // Abrindo o arquivo dino.dat
    if (!inFile)
    {
        std::cerr << "Erro de arquivo! " << std::endl; // Erro se o arquivo não existir.
        return;
    }

    int numPolig, numVertices; // quantidade de poligonos e vertices
    float x, y;
    inFile >> numPolig; // pega o núcleo para saber a quantidade de poligonos
    std::list<Point> vertices;
    for (int i = 0; i < numPolig; ++i)
    {                          // percorrendo todos os poligonos
        inFile >> numVertices; // pegando os vertices
        for (int j = 0; j < numVertices; j++)
        {                             // percorrendo os vertices
            inFile >> x >> y;         // colocando as coordenadas nas variaveis
            pontos.push_back({x, y}); // adicionando na lista de pontos.
        }
    }
    inFile.close();
}

void display()
{
    openFile();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++)
    {                                   // percorrendo a lista
        glVertex2f(ponto->x, ponto->y); // desenhando as linhas
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Dino! ");
    gluOrtho2D(0, 800, 0, 600);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
