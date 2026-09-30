#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    
    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(5.0f);

    glBegin(GL_POINTS);

    
    glVertex2f(-0.8f,  0.8f);   glVertex2f( 0.8f,  0.8f);
    glVertex2f(-0.6f,  0.6f);   glVertex2f( 0.6f,  0.6f);
    glVertex2f(-0.4f,  0.4f);   glVertex2f( 0.4f,  0.4f);
    
    glVertex2f(-0.8f, -0.8f);   glVertex2f( 0.8f, -0.8f);
    glVertex2f(-0.6f, -0.6f);   glVertex2f( 0.6f, -0.6f);
    glVertex2f(-0.4f, -0.4f);   glVertex2f( 0.4f, -0.4f);

    
    glVertex2f(-0.2f,  0.3f);  glVertex2f( 0.0f,  0.3f);  glVertex2f( 0.2f,  0.3f);

    glVertex2f(-0.3f,  0.15f); glVertex2f(-0.1f,  0.15f);
    glVertex2f( 0.1f,  0.15f); glVertex2f( 0.3f,  0.15f);

    glVertex2f(-0.2f,  0.0f);  glVertex2f( 0.0f,  0.0f);  glVertex2f( 0.2f,  0.0f);

    glVertex2f(-0.3f, -0.15f); glVertex2f(-0.1f, -0.15f);
    glVertex2f( 0.1f, -0.15f); glVertex2f( 0.3f, -0.15f);

    glVertex2f(-0.2f, -0.3f);  glVertex2f( 0.0f, -0.3f);  glVertex2f( 0.2f, -0.3f);

    glEnd();
    glFlush();
}

void init() {
   
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Window OpenGL Pertama Saya");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
