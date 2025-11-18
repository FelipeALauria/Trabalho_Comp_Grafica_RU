#ifndef PROJECT_H
#define PROJECT_H

/* ============================
 *  Includes padrão do projeto
 * ============================ */
#include <stdio.h>
#include <stdlib.h>

/* ============================
 *  OpenGL / freeGLUT
 * ============================ */
#include <GL/freeglut.h>

/* ============================
 *  Headers do core
 *  (vão sendo preenchidos aos poucos)
 * ============================ */
#include "camera.h"
#include "cena.h"
#include "interacao.h"

/* ============================
 *  Configuração básica da aplicação
 * ============================ */
typedef struct AppConfig {
    int larguraJanela;
    int alturaJanela;
    const char *tituloJanela;
} AppConfig;

/* ============================
 *  Funções centrais do sistema
 *  (serão implementadas em main.c por enquanto)
 * ============================ */

/**
 * Inicializa o GLUT/freeGLUT, cria a janela
 * e configura parâmetros básicos de OpenGL.
 */
void inicializarAplicacao(int *argc, char **argv, const AppConfig *config);

/**
 * Registra todos os callbacks (teclado, display, reshape, etc.).
 */
void registrarCallbacks(void);

/**
 * Entra no loop principal da biblioteca gráfica (glutMainLoop).
 */
void iniciarLoopPrincipal(void);

#endif /* PROJECT_H */
