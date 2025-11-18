#ifndef CAMERA_H
#define CAMERA_H

#include <GL/freeglut.h>

/* ============================
 *  Estrutura de Câmera
 * ============================ */
typedef struct Camera {
    /* Posição da câmera no mundo */
    float posX, posY, posZ;

    /* Ponto para onde a câmera olha (alvo) */
    float alvoX, alvoY, alvoZ;

    /* Vetor "up" (orientação vertical da câmera) */
    float upX, upY, upZ;

    /* Parâmetros de projeção em perspectiva */
    float fovY;       /* campo de visão vertical em graus */
    float aspect;     /* razão de aspecto: largura / altura */
    float nearPlane;  /* plano de recorte próximo */
    float farPlane;   /* plano de recorte distante */

    /* Orientação em ângulos (estilo FPS) */
    float yaw;        /* rotação em torno do eixo Y (esquerda/direita) */
    float pitch;      /* rotação em torno do eixo X (cima/baixo) */

    /* Parâmetros de controle */
    float velocidadeMovimento;   /* velocidade para WASD */
    float sensibilidadeMouse;    /* sensibilidade do mouse */
} Camera;

/* Câmera principal do sistema (usada pelos callbacks) */
extern Camera gCamera;

/* ============================
 *  Funções da Câmera
 * ============================ */

/* Inicializa a câmera com valores padrão e aspect calculado pela janela */
void cameraInicializar(Camera *cam, int larguraJanela, int alturaJanela);

/* Atualiza apenas o aspect ratio quando a janela é redimensionada */
void cameraAtualizarAspect(Camera *cam, int novaLargura, int novaAltura);

/* Aplica a câmera (projeção + visão) nas matrizes do OpenGL */
void cameraAplicar(const Camera *cam);

/* Movimento em relação à direção da câmera */
void cameraMoverFrente(Camera *cam, float distancia);
void cameraMoverDireita(Camera *cam, float distancia);
void cameraMoverVertical(Camera *cam, float distancia);

/* Processa movimento do mouse (offset em pixels) para girar a câmera */
void cameraProcessarMouse(Camera *cam, float offsetX, float offsetY);

#endif /* CAMERA_H */
