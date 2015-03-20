# to fix: compile manually the mupdf libs first...
# cd mupdf; make
PSP_EBOOT_ICON=data/icon0.png
TARGET=bookr
OBJS:=bkpdf.o bklayer.o bkdocument.o bkmainmenu.o bkfilechooser.o bkpagechooser.o bkcolorschememanager.o bklogo.o bkuser.o bookr.o bkbookmark.o bkpopup.o bkcolorchooser.o bkdjvu.o
OBJS+=bkfancytext.o bkplaintext.o bkpalmdoc.o palmdoc/palm.o
OBJS+=fzrefcount.o fzinstreammem.o fzinstreamstd.o fzimage.o fzimagepng.o fztexture.o fzfont.o fzscreenpsp.o fzscreencommon.o
OBJS+=tinystr.o tinyxmlerror.o tinyxml.o tinyxmlparser.o bkmemcpy.o
OBJS+=res_uifont.o res_txtfont.o res_uitex.o res_logo.o res_uitex2.o
OBJS+=chmlib/chm_lib.o chmlib/lzx.o
OBJS+=vnconv\byteio.o vnconv\charset.o vnconv\data.o vnconv\error.o vnconv\pattern.o
OBJS+=bkcachechooser.o vnconv\webviqrconv.o
OBJS+=pspchm.o

PS2SDK_FREETYPE=C:/Users/Giorgos/psp-ports/trunk/freetype-2.4.12

INCDIR =$(PS2SDK_FREETYPE)/include
CFLAGS = -Imupdf/include -Idjvu/libdjvupsp -G0 -Wall -O2 
#CFLAGS += -g
#BUILD_PRX=1
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =-L$(PS2SDK_FREETYPE)/objs 
LDFLAGS =
LIBS=-Lmupdf/libs -Ldjvu/libs -ldjvulibre -lmupdf -lraster -lworld -lfonts -lstream -lbase -lpspgum -lpspgu -lpsppower -lpsprtc -lpng -lz -ljpeg -lm -lstdc++ -lsupc++ -lfreetype


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Book Reader V8.2

PSPSDK=$(shell psp-config --pspsdk-path)
#USE_PSPSDK_LIBC=1
include $(PSPSDK)/lib/build.mak

res_uifont.c: data/urwgothicb.pfb
	bin2c $< temp res_uifont
	sed s/static// temp > $@
	rm -f temp

res_txtfont.c: data/vera.ttf
	bin2c $< temp res_txtfont
	sed s/static// temp > $@
	rm -f temp

res_uitex.c: data/ui.png
	bin2c $< temp res_uitex
	sed s/static// temp > $@
	rm -f temp

res_uitex2.c: data/ui2.png
	bin2c $< temp res_uitex2
	sed s/static// temp > $@
	rm -f temp

res_logo.c: data/logo.png
	bin2c $< temp res_logo
	sed s/static// temp > $@
	rm -f temp

sce: kxploit
	rm -Rf __SCE__bookr
	rm -Rf __SCE__bookr%
	mv bookr __SCE__bookr
	mv bookr% %__SCE__bookr
