NAME = minishell

MY_LIBFT	=	./libft
MY_PRINTF	=	./libft/ft_printf/
O_DIRECT 	=	./bin/
SRC_DIRECT	=	src/

CC = gcc -Wextra -Werror -Wall -Iinclude

LIBFLAGS = -lreadline -L$(MY_LIBFT) -lft -I$(MY_LIBFT) -L$(MY_PRINTF) -lftprintf -I$(MY_PRINTF)

SRC = main.c builtin.c exec.c signal.c lexer.c utils.c export.c

MY_SOURCES	=	$(addprefix $(SRC_DIRECT), $(SRC))
MY_OBJECTS	=	$(addprefix $(O_DIRECT), $(MY_SOURCES:src/%.c=%.o))

all:	$(NAME)

$(NAME):	$(MY_LIBFT) $(MY_PRINTF) $(O_DIRECT) $(MY_OBJECTS)
	@make -C $(MY_LIBFT)
	@make -C $(MY_PRINTF)
	$(CC) -o $(NAME) $(MY_OBJECTS) $(LIBFLAGS)

clean:
	rm -rf $(MY_OBJECTS)
	rm -rf *.dSYM
	rm -f $(O_DIRECT)*.o

fclean:	clean
	rm -rf $(NAME)
	rm -rf $(O_DIRECT)
	@make fclean -C $(MY_LIBFT)
	@make fclean -C $(MY_PRINTF)

$(O_DIRECT)%.o: src/%.c
	$(CC) -o $@ -c $<

$(O_DIRECT):
	mkdir -p -m 777 $(O_DIRECT)

re:	fclean all

.PHONY:	all clean fclean re