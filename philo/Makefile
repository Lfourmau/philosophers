NAME = philo

SRCS = 	srcs/main.c \
		srcs/utils.c \
		srcs/init_life.c \
		srcs/actions.c \
		srcs/track_end.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

%.o : %.c includes/philo.h
	gcc -c $(CFLAGS) $< -o $(<:.c=.o) -g

$(NAME) : $(OBJS)
	gcc $(CFLAGS) -o philo $(OBJS)

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re