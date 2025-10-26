/* RU, praça de esporte e negócio dos velhos

    Pra compilar gcc <fonte.c> -o <fonte> -lglut -lGL -lGLU –lm
*/

#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>

void display();

void display(){
    glClearColor(0.4 , 0.6, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("RU");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}