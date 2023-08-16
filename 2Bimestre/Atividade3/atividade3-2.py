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

last_x, last_y = 0, 0

def mouse(x, y):
    global last_x, last_y

    delta_x = x - last_x
    delta_y = y - last_y

    last_x = x
    last_y = y

    yaw = -delta_x * 0.01
    pitch = -delta_y * 0.01

    camera.yaw(yaw)
    camera.pitch(pitch)



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
    glutPassiveMotionFunc(mouse)

    glutMainLoop()


if __name__ == "__main__":
    main()
