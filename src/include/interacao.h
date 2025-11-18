#ifndef INTERACAO_H
#define INTERACAO_H

/* Callbacks de interação com o usuário e janela */

/* Redesenho da cena (ligado ao glutDisplayFunc) */
void callbackDisplay(void);

/* Teclado normal (caracteres ASCII) */
void callbackTeclado(unsigned char tecla, int x, int y);

/* Teclado especial (setas, F1, etc.) */
void callbackTecladoEspecial(int tecla, int x, int y);

/* Redimensionamento da janela */
void callbackReshape(int largura, int altura);

/* Movimento do mouse (sem botão pressionado) */
void callbackMouseMovimento(int x, int y);

#endif /* INTERACAO_H */
