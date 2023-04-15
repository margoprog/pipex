/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:49:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/04/15 02:45:16 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	invalid_fd(t_data *data, int fd, int file)
{
	if (fd == -1)
	{
		ft_freetab(data->path);
		free(data->pid);
		if (file == 0)
			return (write(2, "error : file not found\n", 24), exit(1));
		if (file == 1)
			return (write(2, "error : file not created\n", 26), exit(1));
	}
	return ;
}

int	redirection(t_data *data, int index, char **argv)
{
	int	fd_infile;
	int	fd_outfile;

	if (index != data->nbcmd - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	if (index != 0)
	{
		dup2(data->previous, STDIN_FILENO);
		close(data->previous);
	}
	if (index == 0)
	{
		if(data->heredoc == -1)
		{
			fd_infile = data->fd_rdoc[0];
			fprintf(stderr, "test = %d\n", fd_infile);
		}
		else
			fd_infile = open(argv[1], O_RDONLY);
		invalid_fd(data, fd_infile, 0);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
	}
	if (index == data->nbcmd - 1)
	{
		if(data->heredoc == -1)
			fd_outfile = open(argv[index + 3], O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			fd_outfile = open(argv[index + 3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		invalid_fd(data, fd_outfile, 1);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
	return (0);
}

