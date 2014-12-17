IDIR=include
CC=gcc
CFLAGS=-Wall -I$(IDIR)

ODIR=obj
LDIR=lib
SRCDIR=src
LIBS=-lm

_DEPS=fileops.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=jpgenc.o jpgdec.o fileops.o main.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


jpeg-codec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: jpeg-codec

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ jpeg-codec

