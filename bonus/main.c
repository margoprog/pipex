/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:37:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/04/16 05:16:46 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "pipex_bonus.h"

void	here_doc_child(char *limiter, t_data *data)
{
	size_t	size;
	char	*line;

	close(data->fd_rdoc[0]);
	while (1)
	{
		line = get_next_line(0, 0);
		size = ft_strlen(line) - 1;
		if (size > 0 && !ft_strncmp(line, limiter, size))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, data->fd_rdoc[1]);
		free(line);
	}
	get_next_line(0, 1);
	close(data->fd_rdoc[1]);
	exit(0);
}

void	here_doc(char *limiter, t_data *data)
{
	pid_t	pid;

	pipe(data->fd_rdoc);
	pid = fork();
	if (pid == 0)
		here_doc_child(limiter, data);
	else if (pid > 0)
		close(data->fd_rdoc[1]);
	waitpid(pid, 0, 0);
	return ;
}

char	**path_recup(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

int	init_struct(t_data *data, int argc, char **env, char **argv)
{
	data->nbcmd = argc - 3;
	data->heredoc = 0;
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		data->nbcmd = argc - 4;
		data->heredoc = -1;
		here_doc(argv[2], data);
	}
	data->previous = -1;
	data->path = path_recup(env);
	if (!data->path)
		return (write(2, "no path found\n", 14));
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		comp;

	comp = 0;
	if (argc >= 4)
		comp = ft_strcmp(argv[1], "here_doc");
	if ((argc < 5 && comp) || (argc < 6 && !comp))
		return (1);
	if (init_struct(&data, argc, env, argv))
		return (1);
	if (data.heredoc == -1)
		argv += 1;
	ft_pipex(&data, argv, env);
	if (!comp)
		close(data.fd_rdoc[0]);
	return (0);
}
