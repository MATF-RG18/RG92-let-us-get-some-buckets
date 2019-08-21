#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 50

static void init(int, char**);

static void on_display(void);

static void on_keyboard(unsigned char, int, int);

static void on_reshape(int, int);

static void on_timer(int);

int main(int argc, char* argv[])
{
        init(argc, argv);
        
//      Postavlja se boja
        glClearColor(1, 1, 1, 0);
        glEnable(GL_DEPTH_TEST);

        glutMainLoop();

        return 0;
}

static void init(int argc, char* argv[]) {
//      Inicijalizacija aplikacije, kreiranje prozora i pozivanje funkcija
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

        glutInitWindowSize(700, 700);
        glutInitWindowPosition(300, 100);
        glutCreateWindow(argv[0]);

        glutKeyboardFunc(on_keyboard);
        glutReshapeFunc(on_reshape);
        glutDisplayFunc(on_display);
}

static void on_keyboard(unsigned char key, int x, int y)
{
        switch (key) {
                case 27:
                        /* Zavrsava se program. */
                        exit(0);
                        break;
        }
}

static void on_reshape(int width, int height)
{
    /* Postavlja se viewport. */
        glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, (float) width / height, 1, 1500);
}


static void on_timer(int value)
{
        /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
        if(value != 0)
                return;
}

static void on_display(void)
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//      Postavlja se kamera
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
        
        glutSwapBuffers();
}
