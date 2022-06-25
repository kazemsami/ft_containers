NAME = ft_containers
CFLAGS = -Wall -Wextra -Werror
CC = clang++
SRCS = main.cpp

all: ${NAME}

${NAME}:
	${CC} ${CFLAGS} ${SRCS} -std=c++98 -D TESTED_CONT=ft -o $@
	${CC} ${CFLAGS} ${SRCS} -std=c++98 -D TESTED_CONT=std -o std_containers

clean:

fclean: clean
	rm -rf ${NAME}
	rm -rf std_containers

re: fclean all

.PHONY: re fclean clean all
