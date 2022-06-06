/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:55:18 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/06 15:00:33 by fvarrin          ###   ########.fr       */
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
	WORLD_WITH_ENV_EXPENSION,
	WORLD_WITHOUT_ENV_EXPENSION,
	OUTPUT_SIMPLE_OPERATOR,
	OUTPUT_APPEND_OPERATOR,
	INPUT_SIMPLE_OPERATOR,
	INPUT_HEREDOC_OPERATOR
}	t_token_type;

typedef struct s_command {
	char		*in;
	char		*out;
	char		*bin;
	char		**argv;
	t_list_el	*words;
	int			return_value;
	_Bool		out_in_append_mode;
}	t_command;

typedef struct s_token {
	char			*word;
	t_token_type	type;
}	t_token;

typedef struct s_execution_plan {
	t_command	**commands;
	int			number_of_commands;
}	t_execution_plan;

/* Utils */
char				*trim_space(char *source);
int					open_file(char *path, int flags);

/* Prompter */
void				print_welcome_message(void);
char				*prompt(char *line_read);

/* Parser */
t_execution_plan	*init_execution_plan(int number_of_commands);
void				destroy_execution_plan(t_execution_plan *execution_plan);

t_command			*init_command(void);
t_command			*set_command_argv(t_command *command);
void				destroy_command(t_command *command);

t_list_el			*get_io_from_words(t_list_el *words, t_command *command);

t_execution_plan	*parse_line(char *line);

void				delete_word(void *word);
t_list_el			*split_into_words(t_list_el *words, char *command_as_str);

/* Executor */
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

#endif