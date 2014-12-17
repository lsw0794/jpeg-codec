IDIR=../include
CC=gcc
CFLAGS=-Wall -I$(IDIR)

ODIR=obj
LDIR=../lib

LIBS=-lm

_DEPS=fileops.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o jpgenc.o jpgdec.o fileops.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


jpeg-codec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: jpeg-codec

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ jpeg-codec

