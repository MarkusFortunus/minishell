NAME = minishell

CC = gcc -Wextra -Werror -Wall -Iinclude

RLFLAG = -lreadline

SRC =

OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(RLFLAG)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re