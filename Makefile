NAME = diffie_sim
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
SRCS = src/main.c src/ft_math_utils.c src/ft_alice.c src/ft_bob.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
