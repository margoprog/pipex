/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:25:39 by maheraul          #+#    #+#             */
/*   Updated: 2023/03/29 02:24:46 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

typedef struct t_data
{
	char			**path;
	int				nbcmd;
	long long int	*pid;
	int				previous;
	int				fd[2];
}					t_data;

//utils
void	*ft_free_tab(char **tab);
int	ft_error();

#endif