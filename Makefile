NAME = ft_containers
CFLAGS = -Wall -Wextra -Werror
CC = c++
SRCS = main.cpp
OBJS = ${SRCS:.cpp=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -std=c++98 ${OBJS} -o $@

%.o: %.cpp
	${CC} ${CFLAGS} -std=c++98 -c $<

clean:
	rm -rf *.o

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: re fclean clean all