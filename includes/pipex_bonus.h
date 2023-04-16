/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 04:14:21 by maheraul          #+#    #+#             */
/*   Updated: 2023/04/16 04:24:01 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct t_data
{
	int		nbcmd;
	char	**path;
	int		*pid;
	int		previous;
	int		fd[2];
	int		heredoc;
	int		fd_rdoc[2];
}			t_data;

//utils
void		*ft_free_tab(char **tab);
//pipex
char		*write_path(char *cmd, t_data *data);
void		*execute(t_data *data, char *arg, char **env);
void		*free_pipex(t_data *data);
void		*ft_pipex(t_data *data, char **argv, char **env);
//redirection
void		redirect_outfile(t_data *data, int index, char **argv);
int			redirection(t_data *data, int index, char **argv);
void		invalid_fd(t_data *data, int fd, int file, char *file_name);

#endif