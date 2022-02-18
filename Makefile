CC = cc 
CFLAGS = -Wall -Werror -Wextra

HELPERS_SRC = src/helpers/ft_split.c src/helpers/ft_strdup.c \
				src/helpers/ft_strlen.c src/helpers/ft_substr.c \
				src/helpers/ft_strjoin.c \
				src/helpers/ft_strchr.c \
				src/helpers/ft_strcmp.c
UTILITIES_SRC = src/utilities/resolve_cmd.c \
				src/helpers/get_next_line.c \
				src/utilities/init_px.c \
				src/utilities/throw_error.c \
				src/utilities/ft_close.c

PIPEX_SRC = src/pipex.c ${HELPERS_SRC} ${UTILITIES_SRC}

PIPEX_OBJ = ${PIPEX_SRC:.c=.o}
NAME = pipex
.c.o:
	${CC}  -c $< -o $@

all: ${NAME}

bonus: ${NAME}

${NAME} : ${PIPEX_OBJ}
	${CC}  ${PIPEX_OBJ} -o ${NAME}

${PIPEX_OBJ} : ${PIPEX_SRC}

clean:
	rm -rf ${PIPEX_OBJ}
fclean: clean
	rm -rf ${NAME}

.PHONY: all clean fclean
