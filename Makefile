# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 10:27:38 by fvarrin           #+#    #+#              #
#    Updated: 2022/02/17 13:55:47 by fvarrin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# DIRS
ROOT_DIR			?= $(shell pwd)
SRC_DIR				= ${ROOT_DIR}/srcs/
HEADER_DIR			= ${ROOT_DIR}/includes/
LIBFT_DIR			= ${ROOT_DIR}/libft/


# COMPILER
SRC			:= $(addprefix ${SRC_DIR}, main.c parser/parse.c parser/execution-plan.c \
				parser/command.c parser/io.c parser/word.c executor/executor.c \
				executor/pipes.c executor/processes.c prompter/prompt.c \
				common/utils.c)
OBJ			= $(SRC:.c=.o)
NAME 		= minishell
NORM_BIN	= norminette
NORM_FLAGS	= -RCheckForbiddenSourceHeader -RCheckDefine
RM			= rm -f
MACROFLAGS	= -D BIN_NAME=\"${NAME}\"
CFLAGS		= -Wall -Wextra -Werror -I${HEADER_DIR} -I${LIBFT_DIR}includes ${MACROFLAGS} -g -O0
LIBFT_FLAGS	= -L${LIBFT_DIR} -lft
LIB_FLAGS	= -lreadline ${LIBFT_FLAGS}
BUFFER_SIZE	= 1024
CC			= gcc

.PHONY: 	all clean fclean re

${NAME}:	${OBJ}
			@make -C ${LIBFT_DIR} BUFFER_SIZE=${BUFFER_SIZE} all || true
			${CC} ${CFLAGS} ${OBJ} ${LIB_FLAGS} -o ${NAME}

all: 		${NAME}

clean:
			@make -C ${LIBFT_DIR} clean
			${RM} ${OBJ}

fclean: 	clean
			@make -C ${LIBFT_DIR} fclean
			${RM} ${NAME}

re:			fclean ${NAME}

norm:		fclean
			echo "\n\n"
			${NORM_BIN} ${NORM_FLAGS} ${SRC} ${HEADER_DIR}
