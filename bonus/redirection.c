/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:49:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/04/17 03:06:27 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	invalid_fd(t_data *data, int fd, int file, char *file_name)
{
	if (fd == -1)
	{
		ft_freetab(data->path);
		free(data->pid);
		close(data->fd[0]);
		close(data->fd[1]);
		if (data->fd_rdoc[0] != -1)
			close(data->fd_rdoc[0]);
		if (data->previous != -1)
			close(data->previous);
		if (file == 0)
			return (ft_printf("%s: no such file or directory \n", file_name),
				exit(1));
		if (file == 1)
			return (ft_printf("%s: Permission denied\n", file_name), exit(1));
	}
	return ;
}

void	redirect_outfile(t_data *data, int index, char **argv)
{
	int	fd_outfile;

	if (data->heredoc == -1)
		fd_outfile = open(argv[index + 3], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd_outfile = open(argv[index + 3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	invalid_fd(data, fd_outfile, 1, argv[index + 3]);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
}

int	redirection(t_data *data, int index, char **argv)
{
	int	fd_infile;

	if (index != data->nbcmd - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	if (index != 0)
	{
		dup2(data->previous, STDIN_FILENO);
		close(data->previous);
	}
	if (index == 0)
	{
		if (data->heredoc == -1)
			fd_infile = data->fd_rdoc[0];
		else
			fd_infile = open(argv[1], O_RDONLY);
		invalid_fd(data, fd_infile, 0, argv[1]);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	if (index == data->nbcmd - 1)
		redirect_outfile(data, index, argv);
	return (0);
}
