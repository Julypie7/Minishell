# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 13:04:12 by ineimatu          #+#    #+#              #
#    Updated: 2024/08/21 17:19:23 by martalop         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c env_utils.c env_utils2.c lexer_quots.c lexer.c token.c lexer_list.c

OBJ = $(SRC:.c=.o)

CC = cc

RFLAG = -lreadline

CFLAGS = -Wall -Werror -Wextra -fsanitize=address

LIBFT_A = libft/libft.a

all: makelibft $(NAME)

makelibft: 
	make -C libft

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L./libft -lft $(RFLAG)

%.o:%.c Makefile minishell.h lexer.h struct.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)
		make clean -C libft

fclean: clean
		rm -f $(NAME)
		rm -f $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re

