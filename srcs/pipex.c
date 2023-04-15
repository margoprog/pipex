/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:40:18 by maheraul          #+#    #+#             */
/*   Updated: 2023/04/15 03:02:01 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*write_path(char *cmd, t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	while (data->path && data->path[i])
	{
		path = ft_strjoin(data->path[i], "/");
		if (!path)
			return (NULL);
		path = ft_realloc(path, cmd);
		if (access(path, F_OK | X_OK) != -1)
			return (path);
		free(path);
		i++;
	}
	ft_printf("%s: command not found\n", cmd);
	return (NULL);
}

void	*execute(t_data *data, char *arg, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		return (NULL);
	path = write_path(cmd[0], data);
	if (path)
		execve(path, cmd, env);
	ft_free_tab(cmd);
	free(data->pid);
	ft_freetab(data->path);
	exit(1);
	return (NULL);
}

void	*free_pipex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbcmd)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}
	free(data->pid);
	ft_freetab(data->path);
	close(data->fd[0]);
	return (NULL);
}

void	*ft_pipex(t_data *data, char **argv, char **env)
{
	int	i;

	i = -1;
	data->pid = malloc(sizeof(int) * data->nbcmd);
	while (++i < data->nbcmd)
	{
		if (pipe(data->fd) == -1)
			return (write(2, "pipe failed\n", 13), NULL);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			redirection(data, i, argv);
			close(data->fd[0]);
			close(data->fd[1]);
			execute(data, argv[i + 2], env);
		}
		else if (data->pid[i] > 0)
		{
			close(data->fd[1]);
			if (i != 0)
				close(data->previous);
			data->previous = data->fd[0];
		}
	}
	return (free_pipex(data));
}