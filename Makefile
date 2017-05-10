# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droly <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 16:01:54 by droly             #+#    #+#              #
#    Updated: 2017/05/10 18:13:15 by droly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc.so

SRC = free.c             \
	  ft_bzero.c         \
	  malloc.c           \
	  malloc2.c          \
	  realloc.c          \
	  showalloc.c        \
	  ft_putchar.c       \
	  ft_putnbr.c        \
	  ft_putstr.c        \
	  ft_itoa_base_ull.c \
	  ft_strlen.c        \
	  ft_memcpy.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -c

FLAGS2 = -shared -o

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(FLAGS) $(SRC)
	@gcc $(OBJ) $(FLAGS2) $(NAME)
clean:
	@rm -f $(OBJ)
	@echo "Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "Target cleaned."

re: fclean all

.PHONY: all makelibft clean fclean re
