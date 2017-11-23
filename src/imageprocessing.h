
#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H


typedef struct {
  unsigned int width, height;
  float *r, *g, *b;
} imagem;

typedef enum {
	single_thread_lines,
	single_thread_columns,
	fork_lines,
	fork_columns,
	thread_lines,
	thread_columns,
} smp_strategy;

imagem abrir_imagem(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo, imagem *I);
void liberar_imagem(imagem *I);
void aplicar_brilho(float brilho, imagem *I);
float pixel_max(imagem *I);
void dbgmsg(const char *s, ...);
extern int debug;
extern int num_jobs;
extern smp_strategy strategy;

#endif
