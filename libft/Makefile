NAME = libft.a

SRCS = ft_isdigit.c ft_strchr.c ft_strnstr.c ft_atoi.c ft_isprint.c ft_strdup.c ft_strrchr.c ft_bzero.c ft_memchr.c ft_substr.c ft_calloc.c ft_memcmp.c ft_strlcat.c ft_tolower.c ft_isalnum.c ft_memcpy.c ft_strlcpy.c ft_toupper.c ft_isalpha.c ft_memmove.c ft_strlen.c ft_isascii.c ft_memset.c ft_strncmp.c ft_strjoin.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_atod.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstclear.c


OBJS = $(SRCS:.c=.o)

CCFLAGS = -Wall -Werror -Wextra

LIB = ar rcs

CC = gcc

RM = rm -f

#RULES........................................................

all: $(NAME)

$(NAME): $(OBJS)
	$(LIB) $(NAME) $(OBJS)

%.o: %.c Makefile libft.h
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all 

.PHONY: all clean fclean re
