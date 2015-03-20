TARGET_LIB=libapps.a
OBJS=pdfapp.o

PS2SDK_FREETYPE=C:/Users/Giorgos/ps2sdk-ports/trunk/freetype-2.4.12

INCDIR=$(PS2SDK_FREETYPE)/include ../include 
CFLAGS=-G0 -Wall -O2 -I/usr/local/pspdev/psp/include/freetype2
CXXFLAGS=$(CFLAGS) -fno-exceptions -fno-rtti -I/usr/local/pspdev/psp/include/freetype2
ASFLAGS=$(CFLAGS)

LIBDIR=
LDFLAGS=
LIBS=-lpspgu -lz -lm $(PS2SDK_FREETYPE)/objs/libfreetype.a

#EXTRA_TARGETS = EBOOT.PBP
#PSP_EBOOT_TITLE = Bookr - Book Reader

PSPSDK=$(shell psp-config --pspsdk-path)
#USE_PSPSDK_LIBC=1
include $(PSPSDK)/lib/build.mak
