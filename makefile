VERSION = WWTerm-b06
PKGNAME = wwterm-b06

OBJS = terminal.obj termlib.obj lib.obj keyboard.obj keymap.obj com.obj screen.obj escape.obj esclib.obj
OBJS_FULL = D:\\terminal.obj D:\\termlib.obj D:\\lib.obj D:\\keyboard.obj D:\\keymap.obj D:\\com.obj D:\\screen.obj D:\\escape.obj D:\\esclib.obj

.SUFFIXES: .c .obj

terminal.fx :	terminal.bin
	doscmd mkfent16 D:\\terminal.cf

terminal.bin :	$(OBJS)
	echo $(OBJS_FULL) > objs
	doscmd lcc86 -O -o D:\\terminal.bin @D:\\objs

.c.obj :        $*.c
	doscmd lcc86 -c D:\\$*.c -O -I.

clean :
	rm -f terminal.fx terminal.bin *.obj $(PKGNAME).zip

package :	terminal.bin terminal.fx
	mkdir -p $(PKGNAME)
	rm -fR $(PKGNAME)/*
	cp COPYING COPYRIGHT OMAKE.jpn README README.sjis makefile \
		*.h *.c *.bin *.cf *.fx $(PKGNAME)
	zip -r $(PKGNAME) $(PKGNAME)
