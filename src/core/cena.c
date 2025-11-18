#include "project.h"

/* Desenha um cubo simples como placeholder */
static void desenharCuboPlaceholder(void)
{
    glColor3f(0.2f, 0.7f, 1.0f);  /* cor azul clara */
    glutSolidCube(2.0);           /* cubo centralizado na origem */
}

void desenharCena(void)
{
    /* Limpa tela com uma cor cinza escura */
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Habilita o Z-buffer */
    glEnable(GL_DEPTH_TEST);

    /* Aplica a câmera global */
    cameraAplicar(&gCamera);

    /* Desenha o cubo padrão no centro da cena */
    desenharCuboPlaceholder();

    /* Troca buffers (double buffering) */
    glutSwapBuffers();
}
