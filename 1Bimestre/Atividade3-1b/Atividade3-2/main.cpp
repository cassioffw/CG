#include <iostream>
#include <fstream>
#include <list>
#include <GL/glut.h>

struct Point {
    float x;
    float y;
};

std::list<Point> pontos;

void openFile()
{
    std::ifstream inFile("C:/Users/Cassio/Desktop/dino.Dat");
    if (!inFile) {
        std::cerr << "Erro de arquivo! " << std::endl;
        return;
    }

    int numPolig, numVertices;
    float x, y;
    inFile >> numPolig;
    std::list<Point> vertices;
    for (int i = 0; i < numPolig; ++i) {
        inFile >> numVertices;
        for (int j = 0; j < numVertices; j++) {
            inFile >> x >> y;
            pontos.push_back({ x, y });
        }
    }
    inFile.close();
}

void display() {
    openFile();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (auto ponto = pontos.begin(); ponto != pontos.end(); ponto++) {
        glVertex2f(ponto->x, ponto->y);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
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
