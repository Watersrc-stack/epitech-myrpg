##
## EPITECH PROJECT, 2023
## my_rpg
## File description:
## Makefile
##

NAME	=	my_rpg

SRC		=	$(shell find src -name '*.c')

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra -I./include

LDFLAGS	=	-l csfml-graphics -l csfml-window

LDFLAGS2	=	-l csfml-system -l csfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDFLAGS2)

clean:
	$(RM) -f $(OBJ)

fclean:	clean
	$(RM) -f $(NAME)

re:	fclean all

debug: fclean
	$(CC) -g3 -o $(NAME) $(SRC) $(CFLAGS) $(LDFLAGS) $(LDFLAGS2)
