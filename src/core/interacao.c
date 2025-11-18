#include "project.h"

/* Tamanho atual da janela (para centralizar o mouse) */
static int windowWidth = 800;
static int windowHeight = 600;

/* Controle do mouse */
static int ignorarWarp = 0;

/* ============================
 *  Callbacks
 * ============================ */

void callbackDisplay(void)
{
    /* Apenas delega o desenho para o módulo da cena */
    desenharCena();
}

void callbackTeclado(unsigned char tecla, int x, int y)
{
    (void)x; /* evita warnings */
    (void)y;

    float vel = gCamera.velocidadeMovimento;

    switch (tecla) {
        case 27: /* ESC */
            exit(0);
            break;

        /* Movimento no plano horizontal (estilo FPS) */
        case 'w':
        case 'W':
            cameraMoverFrente(&gCamera, vel);
            break;

        case 's':
        case 'S':
            cameraMoverFrente(&gCamera, -vel);
            break;

        case 'a':
        case 'A':
            cameraMoverDireita(&gCamera, vel);
            break;

        case 'd':
        case 'D':
            cameraMoverDireita(&gCamera, -vel);
            break;

        /* Movimento vertical: espaço sobe, 'q' desce */
        case ' ':
            cameraMoverVertical(&gCamera, vel);
            break;

        case 'q':
        case 'Q':
            cameraMoverVertical(&gCamera, -vel);
            break;

        case 'r':
        case 'R':
            /* Futuro: resetar câmera, etc. */
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

void callbackTecladoEspecial(int tecla, int x, int y)
{
    (void)x;
    (void)y;

    switch (tecla) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            /* Podemos usar depois para outras interações */
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

void callbackReshape(int largura, int altura)
{
    if (altura == 0) {
        altura = 1;
    }

    /* Atualiza o viewport para ocupar toda a janela */
    glViewport(0, 0, largura, altura);

    /* Atualiza o aspect ratio da câmera global */
    cameraAtualizarAspect(&gCamera, largura, altura);

    /* Atualiza tamanho da janela para controle do mouse */
    windowWidth = largura;
    windowHeight = altura;
}

void callbackMouseMovimento(int x, int y)
{
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;

    /* Evento gerado pelo warp: ignora */
    if (ignorarWarp) {
        ignorarWarp = 0;
        return;
    }

    /* Primeiro movimento: centraliza sem aplicar delta pra não dar tranco */
    static int first = 1;
    if (first) {
        first = 0;
        ignorarWarp = 1;
        glutWarpPointer(centerX, centerY);
        return;
    }

    /* Agora o delta é sempre relativo ao centro da janela */
    float deltaX = (float)(x - centerX);
    float deltaY = (float)(y - centerY);

    cameraProcessarMouse(&gCamera, deltaX, deltaY);

    /* Reposiciona o cursor no centro */
    ignorarWarp = 1;
    glutWarpPointer(centerX, centerY);

    glutPostRedisplay();
}


/* ============================
 *  Registro de Callbacks
 * ============================ */

void registrarCallbacks(void)
{
    glutDisplayFunc(callbackDisplay);
    glutReshapeFunc(callbackReshape);
    glutKeyboardFunc(callbackTeclado);
    glutSpecialFunc(callbackTecladoEspecial);

    /* Movimento do mouse sem clicar (estilo FPS) */
    glutPassiveMotionFunc(callbackMouseMovimento);
 
    glutSetCursor(GLUT_CURSOR_NONE);
    
}
