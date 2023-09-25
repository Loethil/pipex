# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 14:16:37 by mbatteux          #+#    #+#              #
#    Updated: 2023/09/12 14:16:39 by mbatteux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CCC = pipex.c\
	pipex_utils.c\

OOO = $(CCC:.c=.o)

FLAG = -Wall -Wextra -Werror

I = -Ilibft

LIBFT = $(I) -Llibft -lft

all: $(NAME)

$(NAME): $(OOO)
	make -C libft/
	gcc $(OOO) $(LIBFT) $(FLAG) -o $(NAME) -g3
.c.o:
	gcc $(I) $(FLAG) -c $< -o ${<:.c=.o} -g3
clean:
	make clean -C libft/
	rm -f $(OOO)
fclean: clean
	make fclean -C libft/
	rm -f $(NAME)
re: fclean all
