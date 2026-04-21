NAME        = diffie_sim
ATTACK_NAME = diffie_attack

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iinclude

SHARED_SRCS = src/ft_math_utils.c src/ft_alice.c src/ft_bob.c
SHARED_OBJS = $(SHARED_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SHARED_OBJS) src/main.o
	$(CC) $(CFLAGS) $^ -o $(NAME)

attack: $(SHARED_OBJS) src/main_attack.o
	$(CC) $(CFLAGS) $^ -o $(ATTACK_NAME)

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME) $(ATTACK_NAME)

re: fclean all

.PHONY: all attack clean fclean re
