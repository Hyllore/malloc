# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droly <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 16:01:54 by droly             #+#    #+#              #
#    Updated: 2017/02/20 16:02:44 by droly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc.so

SRC = 

OBJ = $(SRC:.c=.o)

HEAD = 

FLAGS = -Wall -Werror -Wextra -shared -o

all: $(NAME)

$(NAME): $(OBJ) makelibft
	@gcc $(FLAGS) $(NAME) $(SRC)
	@gcc $(NAME) libft/libft.a -o $(NAME)

makelibft:
	@make -C libft/
	@echo "Library included"

clean:
	@rm -f $(OBJ)
	@make -C gnl/ clean
	@make -C ft_printf/ clean
	@echo "Objects cleaned."

fclean: clean
	@rm -f $(NAME)
	@make -C gnl/ fclean
	@make -C ft_printf/ fclean
	@echo "Target cleaned."

re: fclean all

.PHONY: all makelibft clean fclean re
