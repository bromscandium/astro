CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c menu.c game.c utils.c

OBJ = $(SRC:.c=.o)

LDFLAGS = -lncurses

TARGET = astro

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

fclean: clean
	rm -f $(TARGET)

re: fclean $(TARGET)

.PHONY: clean fclean re
