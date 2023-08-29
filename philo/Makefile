CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo

SRCS = ./main.c ./utils/utils.c ./utils/lst_utils.c ./routines.c ./time.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
