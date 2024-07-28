CFLAGS = -Wall -Wextra -Werror

Srcs = philosophers.c ft_atoi.c init.c multi_threading_utils_1.c multi_threading_utils_2.c multi_threading_utils_3.c routines.c threads.c
Objs = ${Srcs:.c=.o}
NAME = philo

%.o:%.c philosopher.h
	cc ${CFLAGS} $< -o $@

all: ${NAME}

${NAME}: ${Objs}
	cc ${CFLAGS} -fsanitize=address ${Objs} -o ${NAME} 

clean:
	rm -f ${Objs}

fclean: clean
	rm -f ${NAME}

re: fclean all