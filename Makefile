# Makefile cross: Linux (WSL) + Windows (MSYS2/MinGW64)

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Isrc/include

SRC = src/core/main.c \
      src/core/camera.c \
      src/core/cena.c \
      src/core/interacao.c

UNAME_S := $(shell uname -s)

# Detecta o SO para ajustar libs e nome do executável
ifeq ($(UNAME_S),Linux)
    # WSL / Linux
    LDFLAGS = -lglut -lGLU -lGL -lm
    OUTPUT = build/projeto_cg_core
else
    # MSYS2 / MinGW (Windows)
    LDFLAGS = -lfreeglut -lopengl32 -lglu32 -lm
    OUTPUT = build/projeto_cg_core.exe
endif

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT) $(LDFLAGS)

clean:
	rm -f $(OUTPUT)

.PHONY: all clean
