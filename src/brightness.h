/*
 * Brightness functions
 */

#ifndef BRIGHTNESS_H_
#define BRIGHTNESS_H_

void apply_bright_fork_lines(float brilho, imagem *I, int jobs);
void apply_bright_fork_columns(float brilho, imagem *I, int jobs);
void apply_bright_thread_lines(float brilho, imagem *I, int jobs);
void apply_bright_thread_columns(float brilho, imagem *I, int jobs);
void apply_bright_single_thread_lines(float brilho, imagem *I);
void apply_bright_single_thread_columns(float brilho, imagem *I);

#endif
