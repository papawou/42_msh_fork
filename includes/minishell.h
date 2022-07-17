/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:55:18 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/17 12:31:22 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define FILE_PERMISSION_IF_CREATED 0664

# include "libft.h"

extern char	**environ;

typedef enum e_error_codes {
	ERR_ALLOCATING_MEMORY = 1,
	ERR_OPENING_FILE = 2,
	ERR_FORKING_PROCESS = 3,
}	t_error_codes;

typedef enum e_token_type {
	WORD_WITH_ENV_EXPANSION,
	WORD_WITHOUT_ENV_EXPANSION,
	OUTPUT_SIMPLE_OPERATOR,
	OUTPUT_APPEND_OPERATOR,
	INPUT_SIMPLE_OPERATOR,
	INPUT_HEREDOC_OPERATOR,
	SPACE_DELIMITER,
	PIPE
}	t_token_type;

typedef struct s_command {
	char		*in;
	char		*out;
	char		*bin;
	char		**argv;
	t_list_el	*tokens;
	int			return_value;
	_Bool		out_in_append_mode;
}	t_command;

typedef struct s_token {
	char			*value;
	t_token_type	type;
}	t_token;

typedef struct s_execution_plan {
	t_command	**commands;
	int			number_of_commands;
}	t_execution_plan;

/** Utils **/
char				*trim_space(char *source);
int					open_file(char *path, int flags);

/** Prompter **/
void				print_welcome_message(void);
char				*prompt(char *line_read);

/* Signals */
void				configure_termios(void);
void				set_parent_signals(void);
void				set_child_signals(void);
void				unset_parent_signals(void);

/** Parser **/
t_execution_plan	*parse_line(char *line);

/* Builder */
t_execution_plan	*init_execution_plan(int number_of_commands);
void				destroy_execution_plan(t_execution_plan *execution_plan);

t_token				*init_token(void);
t_command			*init_command(void);

/* Tokenizer */
t_list_el			*tokenize_line(char *line);

_Bool				check_quote_closed(char *str);
void				set_simple_word(char **str, t_token *token);
void				set_double_quote_word(char **str, t_token *token);
void				set_single_quote_word(char **str, t_token *token);
void				set_space_delimiter(char **str, t_token *token);
_Bool				is_a_simple_output(char *str);
_Bool				is_a_append_output(char *str);
_Bool				is_a_simple_input(char *str);
_Bool				is_a_heredoc_input(char *str);
_Bool				is_a_pipe(char *str);
_Bool				is_an_operator(char *str);
void				set_operator(char **str, t_token *token);

_Bool				has_more_tokens(char *str);

/* Parser */
t_execution_plan	*parse_tokens(t_list_el *tokens);

int					count_number_of_commands(t_list_el *tokens);
void				set_io_from_tokens(t_command *command);
void				set_argv_from_tokens(t_command *command);

/** Executor **/
int					execute_plan(t_execution_plan *execution_plan);
void				execute_command(t_execution_plan *execution_plan,
						int **pipes, int index);

int					**create_pipes(int number_of_child_processes, int **pipes);
void				close_pipes_in_child_process(int **pipes,
						int number_of_child_processes, int index);
void				close_pipes_in_main_process(
						int **pipes, int number_of_child_processes);
void				destroy_pipes(int number_of_child_processes, int **pipes);

int					*create_processes(t_execution_plan *execution_plan,
						int *pids, int **pipes);
int					count_total_process(int number_of_child_processes);

void				route_command_io(
						t_command *command,
						int **pipes,
						int index,
						int number_of_commands
						);

#endif