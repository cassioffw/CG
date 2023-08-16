from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from Camera import *

camera = Camera()

def draw_planet():
    glColor3f(0, 0, 1)
    glutSolidSphere(1.3, 20, 20)
    glColor3f(1, 0.6, 0)
    glutSolidTorus(0.5, 1.0, 20, 20)


def draw_ice_cream():
    glColor3f(1.0, 0.9, 0.0)
    glutSolidSphere(1.0, 20, 20)
    glColor3f(0.8, 0.4, 0.0)
    glRotatef(90, 1, 0, 0)
    glutSolidCone(1.1, 2.5, 20, 20)


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    glLoadIdentity()
    camera._set_model_view_matrix()

    glPushMatrix()
    glTranslatef(-1, 0, 0)
    draw_ice_cream()
    glTranslatef(3, 0, 0)
    draw_planet()
    glTranslatef(3.5, 0, 0)
    glutSolidCube(2)
    glPopMatrix()
    glFlush()

light_position = [1.0, 10.0, 25.0, 15.0]
def init_ilumination():
    ambient_light = [0.50, 0.50, 0.50, 10.0]
    diffuse_light = [1.0, 0.14, 0, 10.0]
    specular = [1.0, 1.0, 1.0, 1.0]

    glMaterialfv(GL_FRONT, GL_SPECULAR, specular)
    glMateriali(GL_FRONT, GL_SHININESS, 10)

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light)
    glLightfv(GL_LIGHT0, GL_POSITION, light_position)

    glEnable(GL_COLOR_MATERIAL)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_SMOOTH)

light_enable = True
def keyboard(key, x, y):
    global light_enable
    match(key):
        case b'x':
            light_position[0] -= 1
        case b'y':
            light_position[1] -=1
        case b'X':
            light_position[0] += 1
        case b'Y':
            light_position[1] +=1
        case b'q':
            light_enable = not light_enable
            if light_enable:
                glEnable(GL_LIGHT0)
            else:
                glDisable(GL_LIGHT0)
    glLightfv(GL_LIGHT0, GL_POSITION, light_position)

    glutPostRedisplay()

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(800, 600)
    glutCreateWindow("Desenho")
    glClearColor(0.0, 0.0, 0.0, 1.0)
    camera.set([-5.5, -5, 10], [0, 0, 0], [0, 1, 0])
    camera.set_shape(45, 1, 1.05, 500)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-5, 5, -5, 5, -10, 10)
    glMatrixMode(GL_MODELVIEW)
    glutDisplayFunc(display)
    glutKeyboardFunc(keyboard)
    init_ilumination()
    glutMainLoop()


if __name__ == "__main__":
    main()
