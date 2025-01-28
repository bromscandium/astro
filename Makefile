CC = gcc
CFLAGS = -Wall -Wextra

SRC = main.c menu.c game.c utils.c

OBJ = $(SRC:.c=.o)

LDFLAGS = -lncurses

TARGET = astro

all: $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)