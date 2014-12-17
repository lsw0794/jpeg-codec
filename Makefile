CC=gcc
CFLAGS=-Wall

#LIBS=-lm

DEPS=fileops.h

OBJ=main.o jpgenc.o jpgdec.o fileops.o

%.o: /%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


jpeg-codec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: jpeg-codec

.PHONY: clean

clean:
	rm -f *.o *~ core *~ jpeg-codec

