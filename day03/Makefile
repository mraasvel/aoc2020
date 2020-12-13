# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/03 08:32:05 by mraasvel      #+#    #+#                  #
#    Updated: 2020/12/03 08:42:03 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = a.out
SRC = $(shell find . -name "*.c" -exec basename {} \;)

CC = gcc
DEBUG = -O0 -g -fsanitize=address -fsanitize=leak
LIBFLAG = -L. -lft

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(DEBUG) -o $@ $(SRC) $(LIBFLAG)

fclean:
	rm -f $(NAME)
re: fclean all
