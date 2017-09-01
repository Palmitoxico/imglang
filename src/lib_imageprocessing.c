
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "imageprocessing.h"

#include <FreeImage.h>

/*
  imagem abrir_imagem(char *nome_do_arquivo);
  void salvar_imagem(char *nome_do_arquivo);
  void liberar_imagem(imagem *i);
*/

imagem abrir_imagem(char *nome_do_arquivo) {
	FIBITMAP *bitmapIn;
	int x, y;
	RGBQUAD color;
	imagem I;

	bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

	if (bitmapIn == 0) {
		printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
	} else {
		printf("Arquivo lido corretamente!\n");
	}

	x = FreeImage_GetWidth(bitmapIn);
	y = FreeImage_GetHeight(bitmapIn);

	I.width = x;
	I.height = y;
	I.r = malloc(sizeof(float) * x * y);
	I.g = malloc(sizeof(float) * x * y);
	I.b = malloc(sizeof(float) * x * y);

	for (int i=0; i<x; i++) {
		for (int j=0; j <y; j++) {
			int idx;
			FreeImage_GetPixelColor(bitmapIn, i, j, &color);

			idx = i + (j*x);

			I.r[idx] = color.rgbRed;
			I.g[idx] = color.rgbGreen;
			I.b[idx] = color.rgbBlue;
		}
	}
	return I;
}

float pixel_max(imagem *I)
{
	int img_size = I->height * I->width;
	float  pixval = 0, mean_square = 0, max = 0;
	for (int index = 0; index < img_size; index++) {
		pixval = I->r[index];
		mean_square = pixval * pixval;
		pixval = I->g[index];
		mean_square += pixval * pixval;
		pixval = I->b[index];
		mean_square += pixval * pixval;
		if (mean_square > max) {
			max = mean_square;
		}
	}
	return max;
}

void liberar_imagem(imagem *I) {
	free(I->r);
	free(I->g);
	free(I->b);
}

void aplicar_brilho(float brilho, imagem *I) {
	int img_size = I->height * I->width;
	float  pixval = 0;
	for (int index = 0; index < img_size; index++) {
		pixval = I->r[index] * brilho;
		I->r[index] = (pixval <= 255.0) ? pixval : 255.0;
		pixval = I->g[index] * brilho;
		I->g[index] = (pixval <= 255.0) ? pixval : 255.0;
		pixval = I->b[index] * brilho;
		I->b[index] = (pixval <= 255.0) ? pixval : 255.0;
	}
}

void salvar_imagem(char *nome_do_arquivo, imagem *I) {
	FIBITMAP *bitmapOut;
	RGBQUAD color;

	printf("Salvando imagem %d por %d...\n", I->width, I->height);
	bitmapOut = FreeImage_Allocate(I->width, I->height, 24, 0, 0, 0);

	for (int i=0; i<I->width; i++) {
		for (int j=0; j<I->height; j++) {
			int idx;

			idx = i + (j*I->width);
			color.rgbRed = I->r[idx];
			color.rgbGreen = I->g[idx];
			color.rgbBlue = I->b[idx];

			FreeImage_SetPixelColor(bitmapOut, i, j, &color);
		}
	}

	FreeImage_Save(FIF_JPEG, bitmapOut, nome_do_arquivo, JPEG_DEFAULT);
}

