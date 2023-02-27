# Makefile
# feito por Gabriel Pontarolo
CC = g++
TARGET = argps

# flags
CPPFLAGS = -Wall -g
LDLIBS = -lm -lgmp

# diretorios fonte
VPATH = src:src/abcspie:src/vigenererss:src/shuffle

objs = main.o vigenere.o common.o vigenereDiferente.o abcspie.o shuffle.o

.PHONY: all clean purge

all: $(TARGET)

# ligacao
$(TARGET): $(objs)
	$(CC) $(objs) $(CPPFLAGS) $(LDLIBS) -o $(TARGET)

# compilacao
main.o: abcspie.h vigenere.h vigenereDiferente.h
abcspie.o: abcspie.h
vigenere.o: vigenere.h common.h
vigenereDiferente.o: vigenereDiferente.h common.h
common.o: common.h
shuffle.o: shuffle.h

# limpeza
clean:
	-rm -f $(objs) *~
purge: clean
	-rm -f $(TARGET)

