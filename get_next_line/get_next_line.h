/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 03:35:31 by mohazerr          #+#    #+#             */
/*   Updated: 2023/01/14 06:51:39 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	42
# endif

size_t	ft_gnlstrlen(const char *str);
char	*ft_gnlstrjoin(char const *s1, char const *s2);
void	*ft_gnlcalloc(size_t n);
char	*ft_gnlstrchr(char *s, char x);

char	*get_next_line(int fd, int boolean);
char	*read_first_line(int fd, char *buffer);
char	*get_first_line(char *buffer);
char	*erase_first_line(char *buffer);

#endif