/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:25:39 by maheraul          #+#    #+#             */
/*   Updated: 2023/04/14 02:44:35 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>

typedef struct t_data
{
	int				nbcmd;
	char			**path;
	int				*pid;
	int				previous;
	int				fd[2];
}					t_data;

//utils
void	*ft_free_tab(char **tab);
int	ft_error();
char	*write_path(char *cmd, t_data *data);
void	*execute(t_data *data, char *arg, char **env);
int	redirection(t_data *data, int index, char **argv);
void	*ft_pipex(t_data *data, char **argv, char **env);

#endif