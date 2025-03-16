#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <algorithm>

// Variables globales
float posicionX = 0.0f;       // Posición X 
float posicionY = 0.0f;       // Posición Y
float velocidadX = 0.0f;       // Velocidad horizontal 
float velocidadY = 0.0f;       // Velocidad vertical 
float gravedad = -0.01f;       // Aceleración
bool enElPiso = true;          // Booleano para detectar que esta en el piso


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

// Función principal de renderizado
void renderizar() {
    glClear(GL_COLOR_BUFFER_BIT); 
    crearPiso();               
    glutSwapBuffers();            
}

// Función principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Practica Extra");

    glutDisplayFunc(renderizar); 

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); 
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);     

    glutMainLoop(); 
    return 0;
}