from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import sys
import math

vertices = []
faces = []
vertex_dict = {}
vertex_to_draw = []
center_x = center_y = center_z = 0

def open_file():
    with open('C:/Users/Cassio/Desktop/g.obj', 'r') as file:
        for line in file:
            line = line.strip()
            if line and not line.startswith('#'):
                elements = line.split()
                if elements[0] == 'v' and (elements[1] != 't' or elements[1] != 'n'):
                    x, y, z = map(float, elements[1:])
                    vertices.append([x, y, z])
                elif elements[0] == 'f':
                    face = [int(index.split('/')[0]) for index in elements[1:]]
                    faces.append(face)
    for index, vertex in enumerate(vertices):
        vertex_dict[index + 1] = vertex

def center_mass():
    total_points = len(vertex_to_draw)
    sum_x = sum(vertex[0] for vertex in vertex_to_draw)
    sum_y = sum(vertex[1] for vertex in vertex_to_draw)
    sum_z = sum(vertex[2] for vertex in vertex_to_draw)

    center_x = sum_x/total_points
    center_y = sum_y/total_points
    center_z = sum_z/total_points

def compare():
    global groups_vertex
    for face in faces:
        for vertex_index in face:
            if vertex_index in vertex_dict:
                vertex_to_draw.append(vertex_dict[vertex_index]) 
    groups_vertex = [vertex_to_draw[i:i+4] for i in range(0, len(vertex_to_draw), 4)]

def rotateX(angle):
    for i, vertex in enumerate(vertex_to_draw):
        x = vertex[0]
        y = (vertex[1] - center_y) * math.cos(angle) - (vertex[2] - center_z) * math.sin(angle) + center_y
        z = (vertex[1] - center_y) * math.sin(angle) + (vertex[2] - center_z) * math.cos(angle) + center_z
        vertex_to_draw[i] = [x, y, z]

def rotateY(angle):
    for i, vertex in enumerate(vertex_to_draw):
        x = (vertex[2] - center_z) * math.cos(angle) - (vertex[0] - center_x) * math.sin(angle) + center_x
        y = vertex[1]
        z = (vertex[2] - center_z) * math.sin(angle) + (vertex[0] - center_x) * math.cos(angle) + center_z
        vertex_to_draw[i] = [x, y, z]

def rotateZ(angle):
    for i, vertex in enumerate(vertex_to_draw):
        x = (vertex[0] - center_y) * math.cos(angle) - (vertex[1] - center_y) * math.sin(angle) + center_x
        y = (vertex[0] - center_y) * math.sin(angle) + (vertex[1] - center_y) * math.cos(angle) + center_y
        z = vertex[2]
        vertex_to_draw[i] = [x, y, z]

def scale(scale_tx):
    tx_scale = 1
    tx_scale += scale_tx
    for i, vertex in enumerate(vertex_to_draw):
        x = (vertex[0] - center_x) * tx_scale + center_x
        y = (vertex[1] - center_y) * tx_scale + center_y
        z = (vertex[2] - center_z) * tx_scale + center_z
        vertex_to_draw[i] = [x, y, z]

def translate(tx_x, tx_y, tx_z):
    for i, vertex in enumerate(vertex_to_draw):
        x = vertex[0] + tx_x
        y = vertex[1] + tx_y
        z = vertex[2] + tx_z
        vertex_to_draw[i] = [x, y, z]


def display():
    glClear(GL_COLOR_BUFFER_BIT)
    groups_vertex = [vertex_to_draw[i:i+4] for i in range(0, len(vertex_to_draw), 4)]
    for group in groups_vertex:
        glBegin(GL_LINE_STRIP)
        for vertex in group:
            glVertex3fv(vertex)
        glEnd()
    glFlush()

def keyboard(key, x, y):
    match key:
        case b"x":
            rotateX(90)
        case b"y":
            rotateY(90)
        case b"z":
            rotateZ(90)
        case b"e":
            scale(0.1)
        case b"q":
            scale(-0.1)
        case b"w":
            translate(0, 0.1, 0)
        case b"s":
            translate(0, -0.1, 0)
        case b"a":
            translate(-0.1, 0, 0)
        case b"d":
            translate(0.1, 0, 0)
        case b"k":
            translate(0, 0, -0.1)
        case b"l":
            translate(0, 0, 0.1)
    glutPostRedisplay()

def menu_cor(op):
    match(op):
        case 0:
            glColor3f(1, 0, 0)
        case 1:
            glColor3f(0, 1, 0)
        case 2:
            glColor3f(0, 0, 1)
    glutPostRedisplay()

def cria_menu():
    sub_menu1 = glutCreateMenu(menu_cor)
    glutAddMenuEntry("Red", 0)
    glutAddMenuEntry("Green", 1)
    glutAddMenuEntry("Blue", 2)
    glutAttachMenu(GLUT_RIGHT_BUTTON)

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(500, 500)
    glutCreateWindow("")
    glutDisplayFunc(display)
    glutKeyboardFunc(keyboard)
    glClearColor(0.0, 0.0, 0.0, 1.0)
    glOrtho(-2, 2, -2, 2, -10, 10)
    open_file()
    compare()
    center_mass()
    cria_menu()
    glutMainLoop()

main()