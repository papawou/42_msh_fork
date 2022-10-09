/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:21:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/09 11:50:37 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <signal.h>

/**
 *
 * Write a line break, clear the tmp file and exit with right status code
 *
 * @param {int} status unused
 */
static	void	heredoc_sigint_handler(int status __attribute__((unused)))
{
	int		tmp_file_fd;

	write(1, "\n", 1);
	if (open_tmp_file(&tmp_file_fd))
		close(tmp_file_fd);
	exit(130);
}

void	set_heredoc_signals(void)
{
	static struct sigaction	act_sigint
		= {.sa_handler = heredoc_sigint_handler, .sa_flags = SA_RESTART};

	signal(SIGQUIT, SIG_IGN);
	sigfillset(&act_sigint.sa_mask);
	sigaction(SIGINT, &act_sigint, NULL);
}

/**
 * Prompt the user for the next command.
 * It frees line_read if already set and allocate memory for the next line.
 *
 * @param {char *} line_read
 *
 * @return {char *} line_read
 */
static char	*prompt_heredoc(char *line_read)
{
	char	*prompt_name;

	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	prompt_name = ft_strdup("> ");
	line_read = readline(prompt_name);
	free(prompt_name);
	return (line_read);
}

/**
 *
 * @param {char *} delimiter
 * @param {int} tmp_file_fd
 */
void	execute_heredoc(t_list_el *env, char *delimiter, int tmp_file_fd)
{
	char	*line_read;
	int		line_number;

	line_number = 0;
	line_read = NULL;
	while (FOREVER)
	{
		++line_number;
		line_read = prompt_heredoc(line_read);
		if (!line_read)
		{
			ft_printf_fd(2,
				"%s: %s %d delimited by end-of-file (wanted `%s`)\n",
				SHELL_NAME, "warning: here-document at line",
				line_number, delimiter);
			break ;
		}
		if (ft_strcmp(line_read, delimiter) == 0)
			break ;
		while (string_has_env_variable(line_read))
			line_read = expand_env_variables_string(env, line_read);
		ft_printf_fd(tmp_file_fd, "%s\n", line_read);
	}
	free(line_read);
}
