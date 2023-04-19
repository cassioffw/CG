#include <iostream>
#include <fstream>
#include <GL/glut.h>

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
    for (int i = 0; i < numPolig; ++i)
    {                          // percorrendo todos os poligonos
        inFile >> numVertices; // pegando os vertices
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < numVertices; j++) { //percorrendo todos os vértices
            inFile >> x >> y; // pegando as coordenadas no arquivo
            glVertex2f(x, y); // fazendo o desenho com o LINE STRIP através das coordenadas
        }
        glEnd();
    }
    inFile.close();
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    openFile();
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
