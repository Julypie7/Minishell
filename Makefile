NAME = minishell

SRC = main.c env_utils.c env_utils2.c lexer_quots.c lexer.c token.c lexer_list.c err_messags.c exec_clean.c exec_utils.c pipex_utils.c syntax_err.c tkn_to_cmd.c parsing_utils.c exec_utils2.c redir_utils.c

OBJ = $(SRC:.c=.o)

CC = cc

RFLAG = -lreadline

CFLAGS = -fsanitize=address #-Wall -Werror -Wextra

LIBFT_A = libft/libft.a

all: makelibft $(NAME)

makelibft: 
	make -C libft

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L./libft -lft $(RFLAG)

%.o:%.c Makefile minishell.h lexer.h struct.h execution.h parsing.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)
		make clean -C libft

fclean: clean
		rm -f $(NAME)
		rm -f $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re

