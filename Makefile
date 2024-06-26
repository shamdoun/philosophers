CFLAGS = -Wall -Wextra -Werror

Srcs = philosophers.c ft_atoi.c init.c multi_threading_utils_1.c multi_threading_utils_2.c routines.c threads.c
Objs = ${Srcs:.c=.o}
NAME = philosophers

%.o:%.c philosopher.h
	cc ${CFLAGS} $< -o $@

all: ${NAME}

${NAME}: ${Objs}
	cc ${CFLAGS} -fsanitize=thread -g ${Objs} -o ${NAME} 

clean:
	rm ${Objs}

fclean: clean
	rm ${NAME}

re: fclean all