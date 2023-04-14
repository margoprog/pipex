/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:37:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/04/14 02:45:52 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	init_struct(t_data *data, int argc, char **env)
{
	data->nbcmd = argc - 3;
	data->previous = -1;
	data->path = path_recup(env);
	if (!data->path)
		return (write(2, "malloc failed", 13));
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (init_struct(&data, argc, env))
		return (1);
	ft_pipex(&data, argv, env);
	return (0);
}
