VERSION = WWTerm-1.0
PKGNAME = wwterm-1.0

OBJS = terminal.obj termlib.obj lib.obj keyboard.obj keymap.obj com.obj screen.obj escape.obj esclib.obj log.obj
OBJS_FULL = D:\\terminal.obj D:\\termlib.obj D:\\lib.obj D:\\keyboard.obj D:\\keymap.obj D:\\com.obj D:\\screen.obj D:\\escape.obj D:\\esclib.obj D:\\log.obj

.SUFFIXES: .c .obj

all :		terminal.fx wwtfunc.fx

terminal.fx :	terminal.bin .doscmdrc
	doscmd mkfent16 D:\\terminal.cf

terminal.bin :	$(OBJS) .doscmdrc
	echo $(OBJS_FULL) > objs
	doscmd lcc86 -O -o D:\\terminal.bin @D:\\objs

.c.obj :	$*.c .doscmdrc
	doscmd lcc86 -c D:\\$*.c -O -I.

wwtfunc.fx :	wwtfunc .doscmdrc
	doscmd mkfent16 D:\\wwtfunc.cf

.doscmdrc :	doscmdrc
	cp doscmdrc .doscmdrc

wonx :
	mkdir -p wonx-2.2
	cp *.[ch] wonx-2.2
	cp makefile_wonx wonx-2.2/makefile
	cd wonx-2.2 ; challsrc.sh *.[ch] ; $(MAKE)

clean :
	rm -f terminal.fx terminal.bin README.sjis wwtfunc.fx \
		*.obj .doscmdrc $(PKGNAME).zip

README.sjis :	README
	cat README | qkc -s -m > README.sjis

package :	all README.sjis
	mkdir -p $(PKGNAME)
	rm -fR $(PKGNAME)/*
	cp COPYING COPYRIGHT OMAKE.jpn README README.sjis \
		makefile makefile_wonx wwtfunc doscmdrc \
		*.h *.c *.bin *.cf *.fx $(PKGNAME)
	zip -r wwterm $(PKGNAME)
	mv wwterm.zip $(PKGNAME).zip
