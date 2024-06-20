NAME = 	libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
SOURCES := ft_printf.c ft_myputchar.c ft_myputstr.c ft_myputnbr.c ft_printptr.c

OBJECTS := $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $@ $^

%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : all clean fclean re


clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
