#include "libft.h"
#include <errno.h>

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define F_NEXISTS 0
#define F_EXISTS 1<<0
#define F_DIRECTORY 1<<1
#define F_EXEC 1<<2
#define F_READ 1<<3

int exit_perror(char *path, int ft_errno, int exit_code)
{
	errno = ft_errno;
	perror(path);
	return (exit_code);
}

int	file_status(char *file)
{
	struct stat	f_info;
	int	r;

	r = F_NEXISTS;
	if (stat(file, &f_info) < 0)
		return (r);
	r |= F_EXISTS;
	if (S_ISDIR(f_info.st_mode))
		r |= F_DIRECTORY;
	if (access(file, X_OK) == 0)
		r |= F_EXEC;
	if (access(file, R_OK) == 0)
		r |= F_READ;
	return (r);
}

int execve_process_error(char *command, int execve_errno)
{
	int		exit_code;
	int		f_status;
	
	f_status = file_status(command);
	exit_code = 126;
	if (execve_errno != ENOEXEC)
	{
		exit_code = (execve_errno == ENOENT) ? 127 : 126; //127 command not found, 126 no exec
		if (f_status & F_DIRECTORY)
			return (exit_perror(command, EISDIR, exit_code));
		else if (!((f_status & F_EXEC) && !(f_status & F_DIRECTORY)))
			return (exit_perror(command, execve_errno, exit_code));
		else if (execve_errno == E2BIG || execve_errno == ENOMEM)
			return (exit_perror(command, execve_errno, 2));
		else if (execve_errno == ENOENT)
		{
			char	*tmp;
			errno = execve_errno;
			tmp = ft_strjoin(command, ": cannot execute: required file not found\n");
			ft_putstr_fd(tmp, 2);
			free(tmp); //return exit_code
			return (exit_code);
		}
		else
		{
			//#if def bash script
			// exec bash script ?
			//bash stuff
			//#endif
		}
	}
	return (exit_perror(command, execve_errno, exit_code));
	/**
	 * exec bash script ??
	 * its exectubale
	 * if file empty == SUCCESS
	 * if is text execute as shell command
	 * else return 126 internal error BINARY_FILE ERROR ": cannot execute binary file: %s" + strerror(i)
	**/
}
