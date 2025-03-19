#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <algorithm>

// Variables globales
float posicionX = 0.0f;       // Posición X 
float posicionY = -0.7f;      // Posición Y (inicialmente en el piso)
float velocidadX = 0.0f;      // Velocidad horizontal
float velocidadY = 0.0f;      // Velocidad vertical
float gravedad = -0.01f;      // Aceleración
bool enElPiso = true;         // Booleano para detectar que está en el piso
float tamañoPersonaje = 0.2f; // Tamaño del personaje
float velocidadBala = 0.05f; // Velocidad base de la bala

// Estructura para las balas
struct Bala {
    float posX, posY;
    float velocidadX, velocidadY;
};

std::vector<Bala> balas;

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

// Crear una bala
void crearBala(float posX, float posY, float velocidadX, float velocidadY) {
    glColor3f(0.0f, 0.0f, 1.0f); 
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f); 
    glBegin(GL_QUADS); 
    glVertex2f(-0.02f, -0.02f);
    glVertex2f(0.02f, -0.02f);
    glVertex2f(0.02f, 0.02f);
    glVertex2f(-0.02f, 0.02f);
    glEnd();
    glPopMatrix();
}

// Función principal de renderizado
void renderizar() {
    glClear(GL_COLOR_BUFFER_BIT); 
    crearPiso();               
    crearPersonaje();        

    // Dibujar las balas
    for (const auto& bala : balas) {
        crearBala(bala.posX, bala.posY, bala.velocidadX, bala.velocidadY);
    }

    glutSwapBuffers();            
}

void actualizar(int value) {
    // Actualizar posición del personaje
    posicionX += velocidadX;

    if (!enElPiso) {
        velocidadY += gravedad;
        posicionY += velocidadY;
    }

    // Verificar colisión con el piso
    if (posicionY - tamañoPersonaje / 2 <= -0.8f) {
        posicionY = -0.8f + tamañoPersonaje / 2;
        velocidadY = 0.0f;
        enElPiso = true;
    }

    //Limites pantalla para el personaje
    if (posicionX - tamañoPersonaje / 2 < -1.0f) {
        posicionX = -1.0f + tamañoPersonaje / 2;
    }
    if (posicionX + tamañoPersonaje / 2 > 1.0f) {
        posicionX = 1.0f - tamañoPersonaje / 2;
    }

    // Actualizar posición de las balas
    for (auto& bala : balas) {
        bala.posX += bala.velocidadX;
        bala.posY += bala.velocidadY;
    }

    glutPostRedisplay();
    glutTimerFunc(16, actualizar, 0); // Llamar a la función de actualización cada 16 ms 
}

// Función para manejar las teclas
void manejarTeclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': // Mover a la izquierda
            velocidadX = -0.02f;
            break;
        case 'd': // Mover a la derecha
            velocidadX = 0.02f; 
            break;
        case 'w': // Para saltar
            if (enElPiso) {
                velocidadY = 0.15f;
                enElPiso = false;
            }
            break;
        case ' ': // Disparar
            {
                Bala nuevaBala;
                nuevaBala.posX = posicionX;
                nuevaBala.posY = posicionY;

                // Suma la velocidad si el personaje se va moviendo hacia adelante 
                if (velocidadX > 0) {
                    nuevaBala.velocidadX = velocidadBala + velocidadX;
                }
                else {
                    nuevaBala.velocidadX = velocidadBala;
                }

                balas.push_back(nuevaBala);
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