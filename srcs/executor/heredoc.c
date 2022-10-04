/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:21:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/02 14:14:43 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <readline/readline.h>

/**
 * Prompt the user for the next command.
 * It frees line_read if already set and allocate memory for the next line.
 *
 * @param {char *} line_read
 *
 * @return {char *} line_read
 */
char	*prompt_heredoc(char *line_read)
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

_Bool	open_tmp_file(int *tmp_file_fd)
{
	*tmp_file_fd = open_file(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC);
	if (*tmp_file_fd < 1)
	{
		print_custom_error("heredoc", NULL, "Could not create temp file");
		return (false);
	}
	ft_printf_fd(*tmp_file_fd, "");
	return (true);
}

/**
 *
 * Prompt for heredoc and write it to a tmp file
 *
 * @param {t_command *} command
 */
void	execute_heredoc(t_command *command)
{
	char	*line_read;
	int		tmp_file_fd;
	int		no_line;

	no_line = 0;
	line_read = NULL;
	open_tmp_file(&tmp_file_fd);
	while (42)
	{
		++no_line;
		line_read = prompt_heredoc(line_read);
		if (!line_read)
		{
			ft_printf_fd(2, "%s: warning: here-document at line %d delimited by end-of-file (wanted `%s')",
				SHELL_NAME, no_line, command->heredoc);
			break ;
		}
		if (ft_strcmp(line_read, command->heredoc) == 0)
			break ;
		ft_printf_fd(tmp_file_fd, "%s\n", line_read);
	}
	free(line_read);
	close(tmp_file_fd);
}
