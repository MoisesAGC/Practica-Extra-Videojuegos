#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <algorithm>

// Variables globales
float posicionX = 0.0f;       // Posición X 
float posicionY = -0.7f;      // Posición Y (inicialmente en el piso)
float velocidadX = 0.5f;      // Velocidad horizontal 
float velocidadY = 0.0f;      // Velocidad vertical 
float gravedad = -0.01f;      // Aceleración
bool enElPiso = true;         // Booleano para detectar que está en el piso
float tamañoPersonaje = 0.2f;  // tamaño del personaj

// Crear el piso
void crearPiso() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);          
    glVertex2f(-1.0f, -0.8f);    
    glVertex2f(1.0f, -0.8f);     
    glVertex2f(1.0f, -1.0f);     
    glVertex2f(-1.0f, -1.0f);    
    glEnd();
}

// Crear el personaje (cuadrado)
void crearPersonaje() {
    glColor3f(1.0f, 0.0f, 0.0f); 
    glPushMatrix();
    glTranslatef(posicionX, posicionY, 0.0f); 
    glBegin(GL_QUADS); 
    glVertex2f(-tamañoPersonaje / 2, -tamañoPersonaje / 2);
    glVertex2f(tamañoPersonaje / 2, -tamañoPersonaje / 2);
    glVertex2f(tamañoPersonaje / 2, tamañoPersonaje / 2);
    glVertex2f(-tamañoPersonaje / 2, tamañoPersonaje / 2);
    glEnd();
    glPopMatrix();
}

// Función principal de renderizado
void renderizar() {
    glClear(GL_COLOR_BUFFER_BIT); 
    crearPiso();               
    crearPersonaje();        
    glutSwapBuffers();            
}

// Función para actualizar la posicion del jugador
void actualizar(int value) {
    if (!enElPiso) {
        velocidadY += gravedad;
        posicionY += velocidadY;
    }

    if (posicionY - tamañoPersonaje /2  <= -0.8f) {
        posicionY = -0.8f + tamañoPersonaje/ 2;
        velocidadY = 0.0f;
        enElPiso = true;
    }

    if (posicionX - tamañoPersonaje /2 < -1.0f) {
        posicionX = -1.0f + tamañoPersonaje /2;
    }
    if (posicionX + tamañoPersonaje /2 > 1.0f) {
        posicionX = 1.0f - tamañoPersonaje /2;
    }

    glutPostRedisplay();
    glutTimerFunc(16, actualizar, 0); // Llamar a la función de actualización cada 16 ms 
}

// Función para manejar las teclas
void manejarTeclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': // Mover a la izquierda
            posicionX -= velocidadX;
            break;
        case 'd': // Mover a la derecha
            posicionX += velocidadX;
            break;
        case ' ': // Espacio para saltar
            if (enElPiso) {
                velocidadY = 0.15f;
                enElPiso = false;
            }
            break;
    }
}

// Función principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Practica Extra");

    glutDisplayFunc(renderizar); 
    glutKeyboardFunc(manejarTeclado); 
    glutTimerFunc(0, actualizar, 0); 

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); 
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);     

    glutMainLoop(); 
    return 0;
}