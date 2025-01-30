CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses

SRC = main.c menu.c levels.c game.c shop.c

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