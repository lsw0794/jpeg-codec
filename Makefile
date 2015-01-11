# Compiler is gcc for C
CC = gcc

# Compiler flags:
#	-g 		adds debugging information
#	-Wall	turns on most, but not all, compiler warnings
CFLAGS = -g -Wall

# define include dirs
INCLUDES = -Iinclude

# define C source files
SRCS = main.c jpgenc.c jpgdec.c fileops.c

# Define the C object files
# This uses the suffix replacement within a macro:
#	$(name:string1=string2)
# For each word in "name", replace "string1" with "string 2"
# So below, we're replacing the .c suffix in all words in SRCS
# with .o suffix
OBJS = $(SRCS:.c=.o)

# Define the main executable file
MAIN = jpeg-codec

.PHONY: depend clean

all: $(MAIN)
	@echo jpeg-codec has been compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)

# This is a suffix replacement rule for building .o's from .c's
# It uses automatic variables 
# $< : the name of the prerequisite rule (a .c file)
# $@ : the name of the target of the rule (a .o file)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend:
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
