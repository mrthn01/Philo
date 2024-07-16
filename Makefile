NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SOURCE =	main.c \
			ft_controls.c \
			ft_init.c \
			ft_monitor.c \
			ft_routine.c \
			ft_simulation.c \
			ft_utils.c \
			ft_utils2.c

OBJ = ${SOURCE.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
		@${CC} ${CFLAGS} ${SOURCE} -o ${NAME}

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re