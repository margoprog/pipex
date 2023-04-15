/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:37:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/04/15 02:38:34 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
# include "get_next_line.h"

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

void	here_doc(char *limiter, t_data *data)
{
	char	*line;
	size_t	size;
	pid_t 	pid;

	pipe(data->fd_rdoc);
	pid = fork();
	if(pid == 0)
	{
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
	else if(pid > 0)
	{
		close(data->fd_rdoc[1]);
	}
	waitpid(pid, 0, 0);
	return ;
}

int	init_struct(t_data *data, int argc, char **env, char **argv)
{
	data->nbcmd = argc - 3;
	data->heredoc = 0;
	if(!ft_strcmp(argv[1],"here_doc"))
	{
		data->nbcmd = argc - 4;
		data->heredoc = -1;
		here_doc(argv[2], data);
	}
	data->previous = -1;
	data->path = path_recup(env);
	if (!data->path)
		return (write(2, "malloc failed", 13));
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		comp;

	comp = -1;
	if (argc >= 4)
		comp = ft_strcmp(argv[1], "here_doc");
	if ((argc < 4 && comp) || (argc < 5 && !comp) )
		return(1);
	if (init_struct(&data, argc, env, argv))
		return (1);

	if (data.heredoc == -1)
		argv += 1;
	ft_pipex(&data, argv, env);
	return (0);
}
