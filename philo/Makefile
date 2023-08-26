CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

SRCS = ./main.c ./utils/utils.c ./utils/lst_utils.c ./time.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
