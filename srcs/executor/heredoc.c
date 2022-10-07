/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:21:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/08 01:50:24 by kmendes          ###   ########.fr       */
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

static	void heredoc_sigint_handler(int status __attribute__((unused)))
{
	write(1, "\n", 1);
	exit(130);
}

void	set_heredoc_signals()
{
	static struct sigaction act_sigint = {.sa_handler = heredoc_sigint_handler, .sa_flags = SA_RESTART};
	
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

void	execute_heredoc(char *heredoc, int tmp_file_fd)
{
	char	*line_read;
	int		no_line;

	no_line = 0;
	line_read = NULL;
	while (42)
	{
		++no_line;
		line_read = prompt_heredoc(line_read);
		if (!line_read)
		{
			ft_printf_fd(2, "%s: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",
				SHELL_NAME, no_line, heredoc);
			break ;
		}
		if (ft_strcmp(line_read, (char *)heredoc) == 0)
			break ;
		ft_printf_fd(tmp_file_fd, "%s\n", line_read);
	}
	free(line_read);
}
