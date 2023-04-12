/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:15:30 by maheraul          #+#    #+#             */
/*   Updated: 2023/04/12 19:46:43 by maheraul         ###   ########.fr       */
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
	data->previous = -1;
	if (!data->path)
		return (write(2, "Malloc failed\n", 15));
	return (0);
}

/*
						0			1			2			3			4
./pipex	"infile"	"cat -e" |	"grep a" |	"lsblk"		"echo aaa"	"wc -l" "outfile"


*/

int		redirection(t_data *data, int index, char **av)
{
	if (index != data->nbcmd - 1) // 0 1 2 3
	{
		dup2(data->fd[1], STDOUT_FILENO);
	}
	if (index != 0) // 1 2 3 4
	{
		dup2(data->previous, STDIN_FILENO);
		close(data->previous);
	}
	if (index == 0) // 0
	{
		int infilefd = open(av[index + 1], O_RDONLY);
		if (infilefd == -1)
			return (printf("le fichier d'ouverture n'existe pas\n"));
		dup2(infilefd, STDIN_FILENO);
	}
	if (index == data->nbcmd - 1) // 4
	{
		int outfilefd = open(av[index + 3], O_WRONLY | O_CREAT | O_TRUNC );
		if (outfilefd == -1)
			return (printf("le fichier d'ecriture n'existe pas\n"));
		dup2(outfilefd, STDOUT_FILENO);
	}
	return 0;
}

void	*execute(t_data *data, int index, char *cmd, char **env)
{
	char	**tab;
	char	*goodcmd;

	(void)index;
	tab = ft_split(cmd, ' ');
	ft_printf("%s", tab[0]);
	ft_printf("%s", tab[1]);
	goodcmd = path_command(tab[0], data->path);
	if (goodcmd)
		execve(goodcmd, tab, env);
	ft_freetab(tab);

	return (NULL);
}

void	*ft_pipex(t_data *data, char **av, char **env)
{
	int i = 0;

	int	*pid;

	printf("%i\n", data->nbcmd);
	pid = malloc(sizeof(int) * data->nbcmd); //a prot
	while (i < data->nbcmd) // i = 0 : cmd = cat ; i = 1 : cmd = grep ; i = 2 : cmd = wc -l
	{
		pipe(data->fd); // a securiser ? perror?
		pid[i] = fork(); // a securiser ? pas besoin passe pas dans boucle si -1
		if (pid[i] == 0)
		{
			redirection(data, i, av);
			close(data->fd[0]);
			close(data->fd[1]);
			execute(data, i, av[i + 2], env);
			free(pid);
			ft_freetab(data->path);
			exit(1);
		}
		else if (pid[i] > 0)
		{
			//printf("%i %i %i\n", data->previous, data->fd[0], data->fd[1]);
			close(data->fd[1]);
			if (data->previous != -1)
				close(data->previous);
			data->previous = data->fd[0];
		}
		i++;
	}
	for (int i = 0; i < data->nbcmd; i++)
		waitpid(pid[i], NULL, 0);

	close(data->fd[0]);
	free(pid);
	ft_freetab(data->path);
	close(data->fd[0]);
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (init_struct(ac, env, &data))
		return (1);
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
