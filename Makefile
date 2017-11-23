CFLAGS = -std=gnu99 -g -Og
SRCDIR=./src

all: lex.yy.c y.tab.c lib_imageprocessing.o brightness.o
	gcc $(CFLAGS) -omain brightness.o lex.yy.c y.tab.c lib_imageprocessing.o -ll -lpthread -lfreeimage -I$(SRCDIR)

lex.yy.c:$(SRCDIR)/imageprocessing.l
	lex $<

y.tab.c:$(SRCDIR)/imageprocessing.y $(SRCDIR)/imageprocessing.l
	bison -dy $(SRCDIR)/imageprocessing.y

lib_imageprocessing.o:$(SRCDIR)/lib_imageprocessing.c
	gcc $(CFLAGS) -c $<

brightness.o:$(SRCDIR)/brightness.c
	gcc $(CFLAGS) -c $<

clean:
	rm *.h lex.yy.c y.tab.c *.o main
