CFLAGS = -std=gnu99 -g -Og
SRCDIR=./src

all: lex.yy.c y.tab.c lib_imageprocessing.o
	gcc $(CFLAGS) -omain lex.yy.c y.tab.c lib_imageprocessing.o -ll -lfreeimage -I$(SRCDIR)

lex.yy.c:$(SRCDIR)/imageprocessing.l
	lex $(SRCDIR)/imageprocessing.l

y.tab.c:$(SRCDIR)/imageprocessing.y $(SRCDIR)/imageprocessing.l
	bison -dy $(SRCDIR)/imageprocessing.y

lib_imageprocessing.o:$(SRCDIR)/lib_imageprocessing.c
	gcc $(CFLAGS) -c $(SRCDIR)/lib_imageprocessing.c

clean:
	rm *.h lex.yy.c y.tab.c *.o main
