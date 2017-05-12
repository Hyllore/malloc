# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droly <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 16:01:54 by droly             #+#    #+#              #
#    Updated: 2017/05/12 15:39:27 by droly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

SRC = free.c             \
	  free2.c            \
	  ft_bzero.c         \
	  malloc.c           \
	  malloc2.c          \
	  realloc.c          \
	  showalloc.c        \
	  ft_putchar.c       \
	  ft_putnbr.c        \
	  ft_putstr.c        \
	  ft_itoa_base_ull.c \
	  ft_memcpy.c


OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -c

FLAGS2 = -shared -o

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(FLAGS) $(SRC)
	@gcc $(OBJ) $(FLAGS2) $(NAME)
	@rm -f libft_malloc.so
	@ln -s $(NAME) libft_malloc.so

clean:
	@rm -f $(OBJ)
	@echo "Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@rm -f libft_malloc.so
	@echo "Target cleaned."

re: fclean all

.PHONY: all makelibft clean fclean re
