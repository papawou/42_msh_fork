# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 10:27:38 by fvarrin           #+#    #+#              #
#    Updated: 2022/10/11 13:44:21 by kmendes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# DIRS
ROOT_DIR			?= $(shell pwd)
SRC_DIR				= ${ROOT_DIR}/srcs/
HEADER_DIR			= ${ROOT_DIR}/includes/
LIBFT_DIR			= ${ROOT_DIR}/libft/


# COMPILER
SRC			:= $(addprefix ${SRC_DIR}, main.c \
 				parser/parse.c parser/builder/execution-plan.c parser/builder/command.c \
 				parser/builder/token.c \
 				parser/tokenizer/tokenizer.c parser/tokenizer/utils.c parser/tokenizer/word.c \
 				parser/tokenizer/delimiter.c parser/tokenizer/operator.c parser/tokenizer/operator-utils.c parser/tokenizer/pipe.c \
 				parser/parser/parser.c parser/parser/command.c parser/parser/io.c parser/parser/arguments.c \
 				parser/parser/checker.c parser/parser/env-vars.c parser/parser/env-vars-builder.c parser/parser/env-vars-utils.c parser/parser/builtins.c \
				executor/executor.c executor/executor-utils.c executor/pipes.c executor/processes.c executor/io.c executor/heredoc.c \
				executor/heredoc-parent.c executor/path.c executor/file-redirect.c \
				executor/builtins.c executor/builtins/echo.c executor/builtins/cd.c executor/builtins/pwd.c executor/builtins/export.c \
				executor/builtins/unset.c executor/builtins/env.c executor/builtins/exit.c \
				executor/execve-errors.c \
				prompter/prompt.c prompter/signal-handlers.c \
				environ/new_environ.c environ/environ-2d.c \
				common/utils.c common/current-dir.c common/error.c)
OBJ			= $(SRC:.c=.o)
NAME 		= minishell
NORM_BIN	= norminette
NORM_FLAGS	= -RCheckForbiddenSourceHeader -RCheckDefine
RM			= rm -f
MACROFLAGS	= -D BIN_NAME=\"${NAME}\"
CFLAGS		= -Wall -Wextra -Werror -I${HEADER_DIR} -I${LIBFT_DIR}includes -I$(HOME)/.brew/opt/readline/include ${MACROFLAGS} -g -O0
LIBFT_FLAGS	= -L${LIBFT_DIR} -lft
LIB_FLAGS	= -L$(HOME)/.brew/opt/readline/lib -lreadline ${LIBFT_FLAGS}
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
