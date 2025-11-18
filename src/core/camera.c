#include "project.h"
#include <math.h>

/* Definição da câmera global principal */
Camera gCamera;

#define DEG2RAD (3.14159265f / 180.0f)

/* Calcula vetores forward e right a partir de yaw/pitch */
static void cameraCalcularDirecoes(const Camera *cam,
                                   float *fwdX, float *fwdY, float *fwdZ,
                                   float *rightX, float *rightY, float *rightZ)
{
    /* Vetor forward (direção para onde a câmera olha) */
    float yawRad   = cam->yaw   * DEG2RAD;
    float pitchRad = cam->pitch * DEG2RAD;

    float fx = cosf(yawRad) * cosf(pitchRad);
    float fy = sinf(pitchRad);
    float fz = sinf(yawRad) * cosf(pitchRad);

    /* Normaliza forward */
    float len = sqrtf(fx * fx + fy * fy + fz * fz);
    if (len > 0.0f) {
        fx /= len;
        fy /= len;
        fz /= len;
    }

    if (fwdX) *fwdX = fx;
    if (fwdY) *fwdY = fy;
    if (fwdZ) *fwdZ = fz;

    if (rightX && rightY && rightZ) {
        /* Right = normalize( forward x worldUp ) */
        float upX = 0.0f, upY = 1.0f, upZ = 0.0f;

        float rx = upY * fz - upZ * fy;
        float ry = upZ * fx - upX * fz;
        float rz = upX * fy - upY * fx;

        float lenR = sqrtf(rx * rx + ry * ry + rz * rz);
        if (lenR > 0.0f) {
            rx /= lenR;
            ry /= lenR;
            rz /= lenR;
        }

        *rightX = rx;
        *rightY = ry;
        *rightZ = rz;
    }
}

void cameraInicializar(Camera *cam, int larguraJanela, int alturaJanela)
{
    if (alturaJanela == 0) {
        alturaJanela = 1; /* evita divisão por zero */
    }

    /* Posição da câmera (levemente acima e afastada da origem) */
    cam->posX = 0.0f;
    cam->posY = 5.0f;
    cam->posZ = 10.0f;

    /* Alvo inicial no centro da cena (origem) */
    cam->alvoX = 0.0f;
    cam->alvoY = 0.0f;
    cam->alvoZ = 0.0f;

    /* Vetor "up" apontando para +Y */
    cam->upX = 0.0f;
    cam->upY = 1.0f;
    cam->upZ = 0.0f;

    /* Projeção em perspectiva básica */
    cam->fovY      = 60.0f;
    cam->aspect    = (float)larguraJanela / (float)alturaJanela;
    cam->nearPlane = 1.0f;
    cam->farPlane  = 1000.0f;

    /* Orientação inicial: olhando levemente para baixo, para a origem */
    cam->yaw   = -90.0f;  /* olhando aproximadamente para -Z */
    cam->pitch = -15.0f;  /* um pouco para baixo */

    /* Parâmetros de controle */
    cam->velocidadeMovimento = 0.5f;
    cam->sensibilidadeMouse  = 0.01f;

    /* Atualiza também a câmera global principal */
    gCamera = *cam;
}

void cameraAtualizarAspect(Camera *cam, int novaLargura, int novaAltura)
{
    if (novaAltura == 0) {
        novaAltura = 1;
    }
    cam->aspect = (float)novaLargura / (float)novaAltura;
}

void cameraAplicar(const Camera *cam)
{
    float fx, fy, fz;
    cameraCalcularDirecoes(cam, &fx, &fy, &fz, NULL, NULL, NULL);

    /* Atualiza o alvo com base em pos + forward */
    float alvoX = cam->posX + fx;
    float alvoY = cam->posY + fy;
    float alvoZ = cam->posZ + fz;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        cam->fovY,
        cam->aspect,
        cam->nearPlane,
        cam->farPlane
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        cam->posX, cam->posY, cam->posZ,
        alvoX,     alvoY,     alvoZ,
        cam->upX,  cam->upY,  cam->upZ
    );
}

void cameraMoverFrente(Camera *cam, float distancia)
{
    float fx, fy, fz;
    cameraCalcularDirecoes(cam, &fx, &fy, &fz, NULL, NULL, NULL);

    cam->posX += fx * distancia;
    cam->posY += fy * distancia;
    cam->posZ += fz * distancia;
}

void cameraMoverDireita(Camera *cam, float distancia)
{
    float fx, fy, fz;
    float rx, ry, rz;
    cameraCalcularDirecoes(cam, &fx, &fy, &fz, &rx, &ry, &rz);

    cam->posX += rx * distancia;
    cam->posY += ry * distancia;
    cam->posZ += rz * distancia;
}

void cameraMoverVertical(Camera *cam, float distancia)
{
    cam->posY += distancia;
}


void cameraProcessarMouse(Camera *cam, float offsetX, float offsetY)
{
    offsetX *= cam->sensibilidadeMouse;
    offsetY *= cam->sensibilidadeMouse;

    cam->yaw   += offsetX;
    cam->pitch -= offsetY;  /* mover mouse para cima -> olhar para cima */

    /* Limita pitch para não virar de cabeça para baixo */
    if (cam->pitch > 89.0f)  cam->pitch = 89.0f;
    if (cam->pitch < -89.0f) cam->pitch = -89.0f;
}
