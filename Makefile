# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 13:04:12 by ineimatu          #+#    #+#              #
#    Updated: 2024/07/18 16:35:18 by martalop         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c

OBJ = $(SRC:.c=.o)

CC = cc

RFLAG = -lreadline

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): Makefile minishell.h $(OBJ)
		$(CC) $(RFLAG) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:	%.c Makefile minishell.h
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

