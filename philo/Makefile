CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

SRCS = ./src/main.c ./utils/utils.c ./utils/lst_utils.c ./src/routines.c \
		./src/time.c ./utils/routine_utils.c ./src/checks.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
