from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import sys
from Camera import *

vertices = []
faces = []
vertex_dict = {}
vertex_to_draw = []
center_x = center_y = center_z = 0
c = Camera()

def open_file():
    with open('C:/Users/Cassio/Desktop/e.obj', 'r') as file:
        for line in file:
            line = line.strip()
            if line and not line.startswith('#'):
                elements = line.split()
                if elements[0] == 'v' and (elements[1] != 't' or elements[1] != 'n'):
                    x, y, z = map(float, elements[1:])
                    vertices.append([x, y, z])
                elif elements[0] == 'f':
                    face = [int(index.split('/')[0]) for index in elements[1:]]
                    global f
                    f = len(face)
                    faces.append(face)
    for index, vertex in enumerate(vertices):
        vertex_dict[index + 1] = vertex


def compare():
    global groups_vertex
    for face in faces:
        for vertex_index in face:
            if vertex_index in vertex_dict:
                vertex_to_draw.append(vertex_dict[vertex_index])
    groups_vertex = [vertex_to_draw[i:i+f]
                     for i in range(0, len(vertex_to_draw), f)]


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    groups_vertex = [vertex_to_draw[i:i+f]
                     for i in range(0, len(vertex_to_draw), f)]
    for group in groups_vertex:
        glBegin(GL_LINE_STRIP)
        for vertex in group:
            glVertex3fv(vertex)
        glEnd()
    glFlush()


def keyboard(key, x, y):
    match key:
        case b"x":
            c.roll(90)
        case b"y":
            c.pitch(90)
        case b"z":
            c.yaw(90)
        case b"e":
            c.zoom_in(10)
        case b"q":
            c.zoom_out(10)
    glutPostRedisplay()


def init():
    c.set_shape(45, 1.7, 1, 100)
    c.set([0, 0, 30], [0, 0, 0], [0, 1, 0])


def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(500, 500)
    glutCreateWindow("")
    glutDisplayFunc(display)
    glutKeyboardFunc(keyboard)
    glClearColor(0.0, 0.0, 0.0, 1.0)
    glOrtho(-100, 100, -100, 100, -10, 10)
    open_file()
    compare()
    init()
    glutMainLoop()


main()
