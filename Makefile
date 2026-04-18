NAME = codexion

VERSION = 1.1

SRCS =	srcs/codexion.c srcs/err.c srcs/parser.c srcs/simulation.c srcs/coders.c srcs/codexion_helper.c srcs/coders_actions.c

OBJS = $(SRCS:.c=.o)

INC_DIR = includes

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -pthread

%.o: %.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus