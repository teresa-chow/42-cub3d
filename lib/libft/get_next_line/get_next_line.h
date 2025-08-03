/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:00:03 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/02 11:28:55 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# include "../../../include/parse.h"

typedef struct s_tmp	t_tmp;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

char	*get_next_line(int fd, t_tmp *tmp);
int		ft_strlen_gnl(char *str);
char	*ft_strchr_gnl(const char *str, int c);
char	*ft_strjoin_gnl(char *str, char *next_buffer);

#endif
