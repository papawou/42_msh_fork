/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:21:57 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/25 16:23:20 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <fcntl.h>
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

/**
 *
 * Prompt for heredoc and write it to a tmp file
 *
 * @param {t_command *} command
 */
void	execute_heredoc(t_command *command)
{
	char	*line_read;
	char	*heredoc_str;
	int		tmp_file_fd;
	char	*tmp;

	line_read = NULL;
	heredoc_str = ft_strdup("");
	tmp_file_fd = open_file(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC);
	ft_printf_fd(tmp_file_fd, "");
	while (42)
	{
		line_read = prompt_heredoc(line_read);
		if (!line_read)
			break ;
		if (ft_strcmp(line_read, command->heredoc) == 0)
			break ;
		tmp = ft_strjoin(heredoc_str, line_read);
		free(heredoc_str);
		heredoc_str = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	free(line_read);
	ft_printf_fd(tmp_file_fd, "%s", heredoc_str);
	free(heredoc_str);
	close(tmp_file_fd);
}
