# Makefile
# feito por Gabriel Pontarolo
CC = g++
TARGET = rgps

# flags
CPPFLAGS = -Wall -g
LDLIBS = -lm -lgmp

# diretorios fonte
VPATH = src:src/sbcspi:src/vigenererss 

objs = main.o vigenere.o common.o vigenereDiferente.o sbcspi.o

.PHONY: all clean purge

all: $(TARGET)

# ligacao
$(TARGET): $(objs)
	$(CC) $(CPPFLAGS) $(LDLIBS) $(objs) -o rgps

# compilacao
main.o: main.cpp sbcspi.h vigenere.h vigenereDiferente.h
sbcspi.o: sbcspi.cpp sbcspi.h
vigenere.o: vigenere.cpp vigenere.h common.h
vigenereDiferente.o: vigenereDiferente.cpp vigenereDiferente.h common.h
common.o: common.cpp common.h

# limpeza
clean:
	-rm -f $(objs) *~
purge: clean
	-rm -f rgps

