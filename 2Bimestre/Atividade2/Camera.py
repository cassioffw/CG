from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import math

class Camera:    
    def __init__(self):
        self.eye, self.u, self.v, self.n, self.look, self.up = [], [], [], [], [], []
        self.view_angle, self.aspect, self.near_dist, self.far_dist = 0, 0, 0, 0
    
    def dot(self, component, vertex):
        return (component[0] + vertex[0]) + (component[1] + vertex[1]) + (component[2] + vertex[2])

    def cross(self, component, vertex):
        v_cross = []

        v_cross.append((vertex[1] * component[2]) - (component[1] * vertex[2]))
        v_cross.append((vertex[2] * component[0]) - (component[2] * vertex[0]))
        v_cross.append((vertex[0] * component[1]) - (component[0] * vertex[1]))

        return v_cross
    
    def normalize(self, component):
        size = math.sqrt(component[0]**2 + component[1]**2 + component[2]**2)

        component[0] /= size
        component[1] /= size
        component[2] /= size

    def set_shape(self, v_angle, a, n, f):
        self.view_angle = v_angle
        self.aspect = a
        self.near_dist = n
        self.far_dist = f
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(self.view_angle, self.aspect, self.near_dist, self.far_dist)
        glMatrixMode(GL_MODELVIEW)

    def _set_model_view_matrix(self):
        m = []
        eVec = [self.eye[0], self.eye[1], self.eye[2]]
        m.extend([self.u[0], self.v[0], self.n[0], 0.0])
        m.extend([self.u[1], self.v[1], self.n[1], 0.0])
        m.extend([self.u[2], self.v[2], -self.n[2], 0.0])
        m.extend([-self.dot(eVec, self.u), -self.dot(eVec, self.v), -self.dot(eVec, self.n), 1.0])

        glMatrixMode(GL_MODELVIEW)
        glLoadMatrixf(m)

    def set(self, eye, look, up):
        self.eye = eye
        self.look = look
        self.up = up
        self.n = [self.eye[0] - self.look[0], self.eye[1] - self.look[1], self.eye[2] - self.look[2]]
        self.u = [self.cross(self.up, self.n)[0], self.cross(self.up, self.n)[1], self.cross(self.up, self.n)[2]]
        self.normalize(self.n) 
        self.normalize(self.u)
        self.v = [self.cross(self.n, self.u)[0], self.cross(self.n, self.u)[1], self.cross(self.n, self.u)[2]]
        self._set_model_view_matrix()

    def roll(self, angle):
        cs = math.cos(angle)
        sn = math.sin(angle)
        temp = self.u
        self.u = [cs * temp[0] - sn * self.v[0], cs * temp[1] - sn * self.v[1], cs * temp[2] - sn * self.v[2]]
        self.v = [sn * temp[0] + cs * self.v[0], sn * temp[1] + cs * self.v[1], sn * temp[2] + cs * self.v[2]]
        self._set_model_view_matrix()

    def pitch(self, angle):
        cs = math.cos(angle)
        sn = math.sin(angle)
        temp = self.v
        self.v = [cs * temp[0] - sn * self.n[0], cs * temp[1] - sn * self.n[1], cs * temp[2] - sn * self.n[2]]
        self.n = [sn * temp[0] + cs * self.n[0], sn * temp[1] + cs * self.n[1], sn * temp[2] + cs * self.n[2]]
        self._set_model_view_matrix()

    def yaw(self, angle):
        cs = math.cos(angle)
        sn = math.sin(angle)
        temp = self.n
        self.n = [cs * temp[0] - sn * self.u[0], cs * temp[1] - sn * self.u[1], cs * temp[2] - sn * self.u[2]]
        self.u = [sn * temp[0] + cs * self.u[0], sn * temp[1] + cs * self.u[1], sn * temp[2] + cs * self.u[2]]
        self._set_model_view_matrix()

    def zoom_in(self, angle):
        self.view_angle -= angle
        self.set_shape(self.view_angle, self.aspect, self.near_dist, self.far_dist)
        self._set_model_view_matrix()
        
    def zoom_out(self, angle):
        self.view_angle += angle
        self.set_shape(self.view_angle, self.aspect, self.near_dist, self.far_dist)
        self._set_model_view_matrix()
    
        





