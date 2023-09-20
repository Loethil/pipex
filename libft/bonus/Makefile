# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 15:43:13 by mbatteux          #+#    #+#              #
#    Updated: 2023/04/17 15:43:14 by mbatteux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BONUS = libft_bonus.a

NAME = libft.a

FLAG = -Wall -Wextra -Werror

all: $(NAME)
	
$(NAME): fichier_o
	ar rc libft.a ft_*.o
fichier_o:
	gcc -c ft_*.c $(FLAG)
clean:
	rm -rf ft_*.o
$(BONUS): bonus fichier_o
	ar rc libft_bonus.a ft_*.o
bonus:
	gcc -c ft_*bonus.c $(FLAG)
fclean: clean
	rm -rf libft.a
	rm -rf libft_bonus.a
re: fclean all

