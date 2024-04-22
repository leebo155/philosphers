CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -Iinclude
NAME = philo
SRCS = src/ft_atoi.c \
	   src/ft_make_rule.c \
	   src/ft_mutex.c \
	   src/ft_philo_loop.c \
	   src/ft_prepare_philo.c \
	   src/ft_thread_fuction.c \
	   src/main.c 
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $^
