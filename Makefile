##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for the game
##

NAME = Terraria

SRC = 	src/main.c \
		src/menu.c \
		src/button.c \
		src/options/options.c \
		src/options/sliders.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
