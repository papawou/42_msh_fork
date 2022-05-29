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

# COMPILER
SRC			:= $(addprefix ${SRC_DIR}, main.c)
OBJ			= $(SRC:.c=.o)
NAME 		= minishell
NORM_BIN	= norminette
NORM_FLAGS	= -RCheckForbiddenSourceHeader -RCheckDefine
RM			= rm -f
MACROFLAGS	= -D BIN_NAME=\"${NAME}\"
CFLAGS		= -Wall -Wextra -Werror -I${HEADER_DIR} ${MACROFLAGS} -g -O0
LIB_FLAGS	= -lreadline
CC			= gcc

.PHONY: 	all clean fclean re

${NAME}:	${OBJ}
			${CC} ${CFLAGS} ${OBJ} ${LIB_FLAGS} -o ${NAME}

all: 		${NAME}

clean:
			${RM} ${OBJ}

fclean: 	clean
			${RM} ${NAME}

re:			fclean ${NAME}

norm:		fclean
			echo "\n\n"
			${NORM_BIN} ${NORM_FLAGS} ${SRC} ${HEADER_DIR}
