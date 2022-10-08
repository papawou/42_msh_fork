/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file-redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:40:37 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/01 13:59:31 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <fcntl.h>

/**
 *
 * @param {char *} file
 *
 * @return {t_file_redirect *}
 */
t_file_redirect	*init_file_redirect(char *file)
{
	t_file_redirect	*file_redirect;

	file_redirect = (t_file_redirect *)malloc(sizeof(t_file_redirect));
	file_redirect->file = ft_strdup(file);
	file_redirect->file_fd = -1;
	file_redirect->std_copy = -1;
	file_redirect->mode = O_RDONLY;
	return (file_redirect);
}

/**
 *
 * @param {void *} file_redirect_arg
 */
void	destroy_file_redirect(void *file_redirect_arg)
{
	t_file_redirect	*file_redirect;

	file_redirect = (t_file_redirect *)file_redirect_arg;
	if (file_redirect == NULL)
		return ;
	free(file_redirect->file);
	free(file_redirect);
	return ;
}
