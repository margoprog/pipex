/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:15:30 by maheraul          #+#    #+#             */
/*   Updated: 2023/03/29 03:04:06 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>

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

char	*path_command(char *cmd, char **path)
{
	int i = 0;
	char *temp;

	while (path && path[i])
	{
		temp = ft_strjoin(path[i], "/");
		temp = ft_realloc(temp, cmd);
		if (access(temp, F_OK | X_OK) != -1)
			return (temp);
		free(temp);
		i++;
	}
	printf("%s: command not found\n", cmd);
	return (NULL);
}

int init_struct(int ac, char **env, t_data *data)
{
	data->nbcmd = ac - 3;
	data->path = path_recup(env);
	if (!data->path)
		return (write(2, "Malloc failed\n", 15));
	return (0);
}


int		redirection(t_data *data, int index, char **av)
{
	if (index == 0)
	{
		int infilefd = open(av[1], O_RDONLY);
		if (infilefd == -1)
			return (printf("le fichier d'ouverture n'existe pas\n"));
	}
	if (index == data->nbcmd)
}

void	*execute(t_data *data, int index, char *cmd, char **env)
{
	char	**tab;
	char	*goodcmd;

	(void)index;
	tab = ft_split(cmd, ' ');
	goodcmd = path_command(tab[0], data->path);
	execve(goodcmd, tab, env);
	return (NULL);
}

void	*ft_pipex(t_data *data, char **av, char **env)
{
	int i = 0;

	int	*pid;

	printf("%i\n", data->nbcmd);
	pid = malloc(sizeof(int) * data->nbcmd);
	while (i < data->nbcmd)
	{
		pipe(data->fd);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			redirection(data, i, av);
			execute(data, i, av[i + 2], env);
		}
		else if (pid[i] > 0)
		{

		}
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (init_struct(ac, env, &data))
		return (1);
	// char **tab = ft_split(av[2], ' ');
	// path_command(tab[0], data.path);
	ft_pipex(&data, av, env);
	return (0);
}

	// data.fd[0]=  open(av[1], O_RDONLY);
	// ft_printf("File descriptor: %d\n", data.fd[0]);
	// if(data.fd[0] == -1)
	// return(ft_error());
	// data.fd[1]= open(av[ac - 1], O_CREAT, 0666);
	// ft_printf("File 2descriptor: %d\n", data.fd[1]);
	// if(data.fd[1] == -1)
	// return(ft_error());
// data.nbcmd = ac - 3;
// data.pid = malloc(sizeof(long long int) * data.nbcmd);
// i = 0;
// while (i < data.nbcmd)
// {
// 	pipe(data.fd);
// 	data.pid[i] = fork();
// 	if (data.pid[i] == 0)
	// {
	// 	if (i == 0)
	// 		execve("/bin/echo", (char *[3]){"/bin/echo", "cette phrase contient multiple fois la lettre e", NULL}, env);
	// 	if (i == 1)
	// 		execve("/bin/ls", (char *[3]){"/bin/ls", "-R", NULL}, env);
	// 	if (i == 2)
	// 		execve("/bin/wc", (char *[3]){"/bin/wc", "-l", NULL}, env);
	// 	exit(1);
// 	}
// 	else if (data.pid[i] > 0)
// 	{
// 		// process parent
// 	}
// 	i++;
// }
// i = 0;
// while (i < data.nbcmd)
// 	waitpid(data.pid[i++], NULL, 0);

// int main(int ac, char **av, char **env)
// {
// 	char *cmd = "/bin/echo";
// 	char *tab[4] = {"/bin/echo", "-R", "-a", NULL};
// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		char *str = malloc(1000);
// 		execve(cmd, tab, env);
// 		printf("Command not found !!!\n");
// 		// process enfant
// 	}
// 	else if (pid > 0)
// 	{
// 		// process parent
// 	}
// 	printf("JE CONTINUE \n");
// 	return (0);
// }
