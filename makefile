VERSION = WWTerm-0.9
PKGNAME = wwterm-0.9

OBJS = terminal.obj termlib.obj lib.obj keyboard.obj keymap.obj com.obj screen.obj escape.obj esclib.obj log.obj
OBJS_FULL = D:\\terminal.obj D:\\termlib.obj D:\\lib.obj D:\\keyboard.obj D:\\keymap.obj D:\\com.obj D:\\screen.obj D:\\escape.obj D:\\esclib.obj D:\\log.obj

.SUFFIXES: .c .obj

terminal.fx :	terminal.bin
	doscmd mkfent16 D:\\terminal.cf

terminal.bin :	$(OBJS)
	echo $(OBJS_FULL) > objs
	doscmd lcc86 -O -o D:\\terminal.bin @D:\\objs

.c.obj :	$*.c
	doscmd lcc86 -c D:\\$*.c -O -I.

wonx :
	mkdir -p wonx-2.2
	cp *.[ch] wonx-2.2
	cp makefile_wonx wonx-2.2/makefile
	cd wonx-2.2 ; challsrc.sh *.[ch] ; $(MAKE)

clean :
	rm -f terminal.fx terminal.bin *.obj $(PKGNAME).zip

package :	terminal.bin terminal.fx
	mkdir -p $(PKGNAME)
	rm -fR $(PKGNAME)/*
	cp COPYING COPYRIGHT OMAKE.jpn README README.sjis \
		makefile makefile_wonx \
		*.h *.c *.bin *.cf *.fx $(PKGNAME)
	zip -r wwterm $(PKGNAME)
	mv wwterm.zip $(PKGNAME).zip
