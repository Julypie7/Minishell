# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 13:04:12 by ineimatu          #+#    #+#              #
#    Updated: 2024/07/18 13:12:54 by ineimatu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MINISHELL

SRC = main.c

OBJ = $(SRC:.c=.o)

CC = cc -lreadline

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)
		$(MAKE) $(NAME)

$(NAME): Makefle minishell.h $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:	%.c Makefile minishell.h
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

