#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <alloca.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "imageprocessing.h"

int num_jobs = 1;
smp_strategy strategy = single_thread_lines;

void apply_bright_range(float brilho, imagem *I, int start, int end) {
	int index;
	float pixval = 0;
	for (index = start; index < end; index++) {
		pixval = I->r[index] * brilho;
		I->r[index] = (pixval <= 255.0) ? pixval : 255.0;
		pixval = I->g[index] * brilho;
		I->g[index] = (pixval <= 255.0) ? pixval : 255.0;
		pixval = I->b[index] * brilho;
		I->b[index] = (pixval <= 255.0) ? pixval : 255.0;
	}
}

void bright_dispatcher(float brilho, imagem *I, int jobs, pid_t *processes) {
	int img_size = I->height * I->width;
	int segment = img_size / jobs;
	int index, remainer, start, end;

	if (img_size % jobs == 0) {
		remainer = segment;
	} else {
		remainer = img_size % jobs;
	}
	
	for (index = 0; index < jobs; index++) {
		processes[index] = fork();
		if (processes[index] == 0) {
			start = index * segment;
			if (index == jobs - 1) {
				end = start + remainer;
			} else {
				end = start + segment;
			}
			apply_bright_range(brilho, I, start, end);
			exit(0);
		}
	}
}

void apply_bright_single_thread_lines(float brilho, imagem *I) {
	int index, imgsize = I->height * I->width;
	float pixval = 0;
	clock_t start, end;
	
	start = clock();
	for (index = 0; index < imgsize; index++) {
		pixval = I->r[index] * brilho;
		I->r[index] = (pixval <= 255.0) ? pixval : 255.0;
		pixval = I->g[index] * brilho;
		I->g[index] = (pixval <= 255.0) ? pixval : 255.0;
		pixval = I->b[index] * brilho;
		I->b[index] = (pixval <= 255.0) ? pixval : 255.0;
	}
	end = clock();
	
	dbgmsg("Image processing strategy: single thread, operating by lines.\n");
	dbgmsg("Elapsed time: %f seconds.\n", (double)(end - start)/CLOCKS_PER_SEC);
}

void apply_bright_fork_lines(float brilho, imagem *I, int jobs) {
	clock_t start, end;
	pid_t *pids;
	pids = alloca(jobs * sizeof(pid_t));
	
	start = clock();
	bright_dispatcher(brilho, I, jobs, pids);
	for (int i = 0; i < jobs; i++) {
		waitpid(pids[i], NULL, 0);
	}
	end = clock();
	
	dbgmsg("Image processing strategy: fork (%d processes), operating by lines.\n", jobs);
	dbgmsg("Elapsed time: %f seconds.\n", (double)(end - start)/CLOCKS_PER_SEC);
}
