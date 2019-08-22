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

static int timer_active;                // Fleg koji odredjuje stanje tajmera
static float x_basket = 10;   // Trenutne koordinate kosa
static float x_curr = 0, y_curr = 1;    // Trenutne koordinate lopte
static float radius = 0.5;              // Poluprecnik lopte
static float v_b = 0.15;                // Vektorska brzina kretanja obruca
static int animation = 1;               // Fleg koji odredjuje status animacije
static float v_y = 0.1;                 // Vektorska brzina kretanja lopte

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
        switch(key) 
        {
                case 27:
//                         Zavrsava se program
                        exit(0);
                        break;
                case 'g':
                case 'G':
//                         Pokrece se animacija
                        if(!timer_active) 
                        {
                                timer_active = 1;
                                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                        }
                        break;
                case 's':
                case 'S':
//                         Zaustavlja se animacija
                        timer_active = 0;
                        break;
                case 'r':
                case 'R':
                        x_curr = 0;
                        y_curr = 1;
                        x_basket = 10;
                        timer_active = 0;
                        animation = 1;
                        break;
                case 'm':
                case 'M':
                        if(animation){
                                v_y += .7;
                                if(v_y >= .6)
                                        v_y = .6;
                        }
                        break;
        }
}

static void on_reshape(int width, int height)
{
//      Postavlja se viewport
        glViewport(0, 0, width, height);

//      Postavljaju se parametri projekcije
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, (float) width / height, 1, 1500);
}


static void on_timer(int value)
{
//      Proverava se da li callback dolazi od odgovarajuceg tajmera
        if(value != TIMER_ID)
                return;
        
//      Brzina kojom lopta pada
        v_y -= .1;
        if(v_y <= -.3)
                v_y = -.3;
        
        y_curr += v_y;
        
//      Brzina kojom se kos krece i simulacija njegovog kretanja
        x_basket -= v_b;
        if(x_basket <= -10)
                x_basket = 10;
        
        glutPostRedisplay();
        
        if(timer_active)
                glutTimerFunc(50, on_timer, 0);
}

static void on_display(void)
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//      Postavlja se kamera
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
        
//      Implementacija plafona i poda
        glPushMatrix();
                glColor3f(0, 0.3, 0.3);
                glTranslatef(0, 82, 0);
                glutSolidCube(100);
        glPopMatrix();
        
        glPushMatrix();
                glColor3f(0, 0.3, 0.3);
                glTranslatef(0, -75.5, 0);
                glutSolidCube(100);
        glPopMatrix();
                
//      Implementacija lopte
        glPushMatrix();
                glTranslatef(x_curr, y_curr, 0);
                glColor3f(.8, .3, 0);
                glutSolidSphere(radius, 100, 100);
        glPopMatrix();
        
//      Implementacija obruca
        glPushMatrix();
                glRotatef(90, 1, 0, 0);
                glTranslatef(x_basket, 0, 0);
                glColor3f(.7, .1, 0);
                glutSolidTorus(.1, 1, 100, 100);
        glPopMatrix();
        
        glutSwapBuffers();
}
