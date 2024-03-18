CFLAGS = -Wall -Wextra -Werror

Srcs = philosophers.c ft_atoi.c init.c multi_threading_utils_1.c multi_threading_utils_2.c routines.c threads.c
Objs = ${Srcs:.c=.o}
NAME = philosophers

%.o:%.c philosopher.h
	cc ${CFLAGS} $< -o $@

all: ${Target}

${NAME}: ${Objs}
	cc ${CFLAGS} -g ${Objs} -o ${Target} 

clean:
	rm ${Objs}

fclean: clean
	rm ${NAME}

re: fclean all