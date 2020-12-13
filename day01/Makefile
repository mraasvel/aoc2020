# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mraasvel <mraasvel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/02 08:25:18 by mraasvel      #+#    #+#                  #
#    Updated: 2020/12/02 08:43:59 by mraasvel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =  a.out
SRC = main.c get_next_line.c
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
LIB = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJDIR = obj
DEBUG = -O0 -g -fsanitize=address
IFLAG = -I $(IDIR)
LFLAG = -L. -lft
IDIR = .

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $(DEBUG) $(OBJ) $(IFLAG) $(LFLAG)
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c -o $@ $<

$(OBJDIR):
	mkdir -p $@

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
