NAME = minishell

MY_LIBFT	=	./libft
MY_PRINTF	=	./libft/ft_printf/
O_DIRECT 	=	./bin/
SRC_DIRECT	=	src/

CC = gcc -Werror -Wall -Wextra -Iinclude/ -g

LIBFLAGS = -l readline -l ncurses -L$(MY_LIBFT) -lft -I$(MY_LIBFT) -L$(MY_PRINTF) -lftprintf -I$(MY_PRINTF)

SRC = main.c chdir.c echo.c env.c exit.c export_utils.c export.c pwd.c unset.c \
error.c heredoc.c \
builtin.c exec_utils.c exec.c \
ft_fill_stdio_file.c ft_split_quote.c list_builder.c parser.c parsing_error.c quote_dollar_parsing.c redir_parser.c utils_parsing.c \
inoutfile.c pipe.c \
signal.c free.c replace_dollar.c quote_dollar_utils.c

MY_SOURCES	=	$(addprefix $(SRC_DIRECT), $(SRC))
MY_OBJECTS	=	$(addprefix $(O_DIRECT), $(MY_SOURCES:src/%.c=%.o))

all:	rdline $(NAME)

rdline:

	@if [ -x "$$HOME/homebrew/bin/brew" ] || [ -x "$$HOME/.brew/bin/brew" ]; then \
		echo "Brew is already installed"; \
	else \
		echo "Brew not found"; \
		read -p "Do you want to install brew? y/n: "  brewchoice; \
		printf " "; \
		if [ "$$brewchoice" = "y" ]; then \
			rm -rf $$HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $$HOME/.brew && \
			echo 'export PATH=$$HOME/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc && brew update; \
			echo "Brew successfully installed"; \
		else \
			echo "Exit"; \
			exit 2; \
		fi \
	fi
	@if [ -d "$$HOME/homebrew/opt/readline" ] || [ -d "$$HOME/.brew/opt/readline" ]; then \
		echo "Brew/readline is already installed"; \
	else \
		echo "Readline not found"; \
		read -p "Do you want to install readline? y/n: "  brewchoice; \
		printf " "; \
		if [ "$$brewchoice" = "y" ]; then \
			brew install readline ; \
			if [ -d "$$HOME/homebrew/opt/readline" ]; then \
				echo 'export LDFLAGS="-L/Users/$(USER)/homebrew/opt/readline/lib"' >> /Users/$(USER)/.zshrc; \
				echo 'export CPPFLAGS="-I/Users/$(USER)/homebrew/opt/readline/include"' >> /Users/$(USER)/.zshrc; \
			elif [ -d "$$HOME/.brew/opt/readline" ]; then \
				echo 'export LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"' >> /Users/$(USER)/.zshrc; \
				echo 'export CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"' >> /Users/$(USER)/.zshrc; \
			else \
				echo "Export fail"; \
			fi \
		else \
			echo "Exit"; \
			exit 2; \
		fi \
	fi 
	@if [ -f "include/readline/libreadline.a" ] && [ -f "include/readline/libhistory.a" ]; then \
		echo "Readline is already make" ; \
	else \
		cd include/readline && ./configure && make ; \
	fi

$(NAME):	$(MY_LIBFT) $(MY_PRINTF) $(O_DIRECT) $(MY_OBJECTS)
	@make -C $(MY_LIBFT)
	@make -C $(MY_PRINTF)
	$(CC) -o $(NAME) $(MY_OBJECTS) $(LIBFLAGS) include/readline/libhistory.a include/readline/libreadline.a 

$(O_DIRECT)%.o: src/%.c
	$(CC) -o $@ -c $<

$(O_DIRECT)%.o: src/parsing/%.c
	$(CC) -o $@ -c $<

$(O_DIRECT)%.o: src/cmd/%.c
	$(CC) -o $@ -c $<

$(O_DIRECT)%.o: src/redir/%.c
	$(CC) -o $@ -c $<

$(O_DIRECT)%.o: src/error_and_free/%.c
	$(CC) -o $@ -c $<

$(O_DIRECT)%.o: src/execute/%.c
	$(CC) -o $@ -c $<

$(O_DIRECT)%.o: src/signal/%.c
	$(CC) -o $@ -c $<

$(O_DIRECT):
	mkdir -p -m 700 $(O_DIRECT)

clean:
	rm -rf $(MY_OBJECTS)
	rm -rf *.dSYM
	rm -f $(O_DIRECT)*.o

fclean:	clean
	rm -rf $(NAME)
	rm -rf $(O_DIRECT)
	@make fclean -C $(MY_LIBFT)
	@make fclean -C $(MY_PRINTF)

leaks:
	make && leaks --atExit -- ./$(NAME)

supp:
	test -f /tmp/supp.txt || cp supp.txt /tmp

valgrind: all supp
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --suppressions=/tmp/supp.txt ./minishell

re:	fclean all

.PHONY:	all clean fclean re leaks valgrind supp