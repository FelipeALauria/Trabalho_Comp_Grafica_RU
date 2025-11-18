#include "project.h"

/* ============================
 *  Implementação das funções centrais
 * ============================ */

void inicializarAplicacao(int *argc, char **argv, const AppConfig *config)
{
    /* Inicializa o GLUT / freeGLUT */
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    /* Tamanho inicial da janela */
    glutInitWindowSize(config->larguraJanela, config->alturaJanela);

    /* Posição inicial da janela na tela (opcional) */
    glutInitWindowPosition(100, 100);

    /* Cria a janela */
    glutCreateWindow(config->tituloJanela);

    glutFullScreen();

    /* Configuração básica de OpenGL */
    glEnable(GL_DEPTH_TEST);  /* Z-buffer */
    glShadeModel(GL_SMOOTH);  /* shading suave */

    /* Inicializa a câmera principal com base no tamanho da janela */
    cameraInicializar(&gCamera, config->larguraJanela, config->alturaJanela);
}

void iniciarLoopPrincipal(void)
{
    /* Entra no loop principal do GLUT */
    glutMainLoop();
}

/* ============================
 *  Função principal (main)
 * ============================ */

int main(int argc, char **argv)
{
    AppConfig config;

    config.larguraJanela = 800;
    config.alturaJanela  = 600;
    config.tituloJanela  = "Projeto CG - Core";

    /* Inicializa janela, OpenGL e câmera */
    inicializarAplicacao(&argc, argv, &config);

    /* Registra callbacks de desenho / teclado / reshape, etc. */
    registrarCallbacks();

    /* Entra no loop do GLUT (não retorna) */
    iniciarLoopPrincipal();

    return 0;
}
