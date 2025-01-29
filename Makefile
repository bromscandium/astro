CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses

SRC = main.c menu.c game.c utils.c

OBJ = $(SRC:.c=.o)

LDFLAGS = -lncurses

TARGET = astro

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)